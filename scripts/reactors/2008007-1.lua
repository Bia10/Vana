--[[
Copyright (C) 2008-2016 Vana Development Team

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
-- Orbis PQ jail map switches

map = getMap()

levers = {
	[920010930] = {
		{-137, 207, "trap1"}, -- lever1
		{42, 206, "trap2"}, -- lever2
		{-81, -26, "trap3"}, -- lever3
		{-2, -27, "trap4"}, -- lever4
		{-120, -390, "trap5"}, -- lever5
		{30, -390, "trap6"} -- lever6
	}
}

function isInBox(x, y, range_x, range_y)
	userx = getPosX();
	usery = getPosY();
	
	top = y - range_y;
	left = x - range_x;
	bottom = y + range_y;
	right = x + range_x;
	
	-- showWorldMessage("t " .. top .. ", l " .. left .. ", b" .. bottom .. ", right " .. right);
	if (userx >= left and userx <= right) and (usery >= top and usery <= bottom) then
		return true;
	else
		return false;
	end
end

showWorldMessage("wat ");
if levers[map] ~= nil then
	map_levers = levers[map];
	for i = 1, #map_levers do
		lever = map_levers[i];
		showWorldMessage("lever " .. i .. " x " .. lever[1] .. " y " .. lever[2]);
		if isInBox(lever[1], lever[2], 80, 200) then
			setObstacleState(lever[3], 1);
			showWorldMessage("In range");
		end
	end
end

--[[
if map == 920010930 then
	if isInBox(-137, 207, 50, 100) then
		-- lever1
	elseif isInBox(-137, 207, 50, 100) then
		-- lever2
		showWorldMessage("wat");
	elseif isInBox(-137, 207, 50, 100) then
		showWorldMessage("wat");
	elseif isInBox(-137, 207, 50, 100) then
		showWorldMessage("wat");
	end
end
]]--