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
-- Orbis PQ jail map exit

map = getMap()

-- TODO: Check mob count
if map == 920010910 then
	-- Tele to 920010912 when all 9300044 are dead
	setMap(920010911, "out00");
elseif map == 920010920 then
	-- Tele to 920010922 when all 9300044 are dead
	setMap(920010921, "out00");
elseif map == 920010930 then
	-- Tele to 920010932 when all 9300044 are dead
	setMap(920010931, "out00");
end
