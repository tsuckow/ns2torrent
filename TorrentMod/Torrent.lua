NS2TorrentMod = {}

function NS2TorrentMod:OnClientLuaStart()
end

function NS2TorrentMod:OnServerLuaFinished()
end

NS2TorrentMod.mycount = 100
function NS2TorrentMod:TorrentUpdateClient()
	if self.mycount == 0 then
		--Shared.Message( self.myTorrent:getSession() )
		self.mycount = 100
	else
		self.mycount = self.mycount - 1
	end
end

function NS2TorrentMod:OnCommandTorrentDownload(hash)
	 Shared.Message("TorrentDownload " .. hash)
end

function NS2TorrentMod:OnClientConnect(client)
	Shared.Message("TorrentClientConnect")
	if (client ~= nil) then
		Shared.Message("We got client")
        local player = client:GetControllingPlayer()
        
        if (player ~= nil) then
			Shared.Message("TorrentClientConnect Sent COmmand")
			Server.SendCommand(player, "torrentdownload 1234")
		end
	end
end

function NS2TorrentMod:OnLoad()
	Shared.Message( "\n==NS2Torrent Loading==" )
	local entrypoint, msg, where = self:LoadLuaDllModule("NS2Torrent.dll")
	
	if(entrypoint) then
		entrypoint()
	end
	
	self.myTorrent = NS2Torrent.Torrent()
	self.myTorrent:addPeer("66.225.8.15",9999)
	
	if(Client) then
		Shared.Message("Torrent ==Client==")
		--self.myTorrent:doDownload("BAE62A9932EC69BC6687A6D399CCB9D89D00D455")
		
		Event.Hook("SetupCamera", function(...) self:TorrentUpdateClient(); return OnSetupCamera(...) end )
		
		Event.Hook("Console_torrentdownload", function(...) return self:OnCommandTorrentDownload(...); end )
		
	end
	
	if(Server) then
		Shared.Message("Torrent ==Server==")
		Event.Hook("ClientConnect", function(...) return self:OnClientConnect(...); end )
	end
end

function NS2TorrentMod:OnDisable()
end