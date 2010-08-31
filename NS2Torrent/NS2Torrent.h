#pragma once

#include <libtorrent\create_torrent.hpp>
#include <libtorrent\session.hpp>

class NS2Torrent
{
public:
	NS2Torrent(void);
	~NS2Torrent(void);

protected:
		libtorrent::session s;
};

