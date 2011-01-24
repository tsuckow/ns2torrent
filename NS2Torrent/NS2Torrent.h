#pragma once

#include <luabind/luabind.hpp>

#define TORRENT_DISABLE_GEO_IP
#include <libtorrent\session.hpp>
#include <libtorrent\create_torrent.hpp>
#include <libtorrent\alert_types.hpp>

class NS2Torrent
{
public:
	NS2Torrent(void);
	~NS2Torrent(void);

	void addPeer(std::string const & address, int port);
	void doDownload(std::string const & hash);
	std::string getSession();

	void processAlerts();
	void operator()(libtorrent::portmap_alert const& a) const;

	static luabind::scope RegisterClass();

protected:
	libtorrent::session s;
	mutable std::vector<int> upnp_mappings;
	mutable std::vector<int> npmp_mappings;
	libtorrent::torrent_handle th;
};

