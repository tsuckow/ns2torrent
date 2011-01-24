#include "NS2Torrent.h"
#include <utility>

#include <libtorrent\natpmp.hpp>
#include <libtorrent\upnp.hpp>

#include <libtorrent/extensions/metadata_transfer.hpp>
#include <libtorrent/extensions/ut_metadata.hpp>
#include <libtorrent/extensions/ut_pex.hpp>
#include <libtorrent/extensions/smart_ban.hpp>

#include <boost/foreach.hpp>

using namespace libtorrent;
using namespace std;

NS2Torrent::NS2Torrent(void)
{
	s.add_extension(&libtorrent::create_metadata_plugin); //MetaData
	s.add_extension(&libtorrent::create_ut_metadata_plugin); //uTorrent Metadata
	s.add_extension(&libtorrent::create_ut_pex_plugin); //uTorrent Peer Exchange
	s.add_extension(&libtorrent::create_smart_ban_plugin); //Ban non-sane peers

	s.set_max_connections(10);

	//Pick some random port (We prefer to not be the same as other people on lans).
	srand ( time(NULL) );
	int start = rand() % 50000 + 7000;
	s.listen_on( make_pair( start ,60000) );

	//Port forward
	s.start_upnp();
	s.start_natpmp();

	//Local peers (LAN)
	s.start_lsd();

	//Bootstrap
	s.add_dht_router(make_pair("router.bittorrent.com",6881));
	s.add_dht_router(make_pair("router.utorrent.com",6881));
	s.add_dht_router(make_pair("dht.transmissionbt.com",6881));

	std::cout << "Constructed NS2Torrent" << std::endl;
}


NS2Torrent::~NS2Torrent(void)
{
	s.stop_dht();

	s.stop_lsd();

	s.stop_upnp();
	s.stop_natpmp();
	Sleep(500);

	std::cout << "Destructed NS2Torrent" << std::endl;
}

void NS2Torrent::addPeer(string const & address, int port)
{
	s.add_dht_router(make_pair(address,port));
}

void NS2Torrent::doDownload(std::string const & hash)
{
	add_torrent_params params;

	//We using magnet links (from add_magnet_uri)
	if (hash.size() == 40)
		from_hex(hash.c_str(), 40, (char*)&(params.info_hash)[0]);
	else
		params.info_hash.assign(base32decode(hash));

	//params.info_hash = sha1_hash(hash);

	params.duplicate_is_error = false;
	params.save_path = "./NS2Downloads/";

	torrent_handle handle = s.add_torrent( params );
	th = handle;
	bool valid = handle.is_valid();
	bool paused = handle.is_paused();
}

string NS2Torrent::getSession()
{
	bool paused =false;// th.is_paused();
	bool meta = false;//th.has_metadata();
	std::vector<peer_list_entry> peers;
	//th.get_full_peer_list(peers);
	unsigned short port = 0;//s.listen_port();

	//entry e = s.dht_state();
	//entry ee = e.dict()["nodes"];
	size_t nodes = 0;//ee.list().size();

	std::stringstream str;
	str << (paused?" P":"NP") << " ";
	str << (meta?" M":"NM") << " ";
	str << nodes << " ";
	str << peers.size();
	return str.str();
}

luabind::scope NS2Torrent::RegisterClass()
{
	return luabind::class_<NS2Torrent>("Torrent")
		.def( luabind::constructor<>() )
		.def("addPeer", &NS2Torrent::addPeer)
		.def("doDownload", &NS2Torrent::doDownload)
		.def("getSession", &NS2Torrent::getSession)
		;
}