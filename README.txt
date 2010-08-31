Boost goes in the libtorrent folder.

libtorrent is included, but you can build it if you like.

You need a modified luabind. Deathbobomega also hosts a fork with a NS2 branch.

How to build libtorrent:
cd libtorrent*\boost
bootstrap
bjam --build-type=complete runtime-link=static stage
cd ..
bjam openssl=off runtime-link=static debug
bjam openssl=off runtime-link=static release