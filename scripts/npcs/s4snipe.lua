--[[
Copyright (C) 2008-2014 Vana Development Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
--]]
-- Insignificant Being

dofile("scripts/lua_functions/jobFunctions.lua");

if isQuestActive(6108) then
	if getPartyId() == 0 then
		addText("You don't have a  party. You can challenge with party.");
		sendOk();
	elseif isPartyLeader() then
		members = getAllPartyPlayerIds();
		if #members ~= 2 then
			addText("You can make a quest when you have a party with two. Please make your party with two members.");
			sendOk();
		else
			if not isPartyInLevelRange(120, 200) then
				addText("There is a character among your party whose level is not eligible. You should be level 120 above. Please adjust level.");
				sendOk();
			else
				memberCount = 0
				mapId = getMap();
				for i = 1, #members do
					member = members[i];
					if setPlayer(member) then
						if getJobLine() == 3 and getJobProgression() == 2 and getMap() == mapId then -- Only want 4th job bowmen
							memberCount = memberCount + 1;
						end
						revertPlayer();
					end
				end
				if memberCount ~= 2 then
					addText("You can't enter. Your party member's job is not Bow Master or Marksman or Your party doesn't consist of two members.");
					sendOk();
				else
					if not isInstance("snipe4th") then
						createInstance("snipe4th", 20 * 60, true);
						for i = 1, #members do
							addInstancePlayer(members[i]);
						end
						addInstanceParty(getPartyId());
						warpParty(910500000);
					else
						addText("Other parties are challenging on quest clear now. Try again later.");
						sendOk();
					end
				end
			end
		end
	else
		addText("After two Bowmans who made 4th advancement make a party, party leader can take to me.");
		sendOk();
	end
else
	addText("I don't know what you're talking about.");
	sendOk();
end