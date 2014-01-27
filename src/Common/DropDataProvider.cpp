/*
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
*/
#include "DropDataProvider.h"
#include "Database.h"
#include "InitializeCommon.h"
#include "StringUtilities.h"
#include <iomanip>
#include <iostream>
#include <string>

auto DropDataProvider::loadData() -> void {
	std::cout << std::setw(Initializing::OutputWidth) << std::left << "Initializing Drops... ";

	loadDrops();
	loadGlobalDrops();

	std::cout << "DONE" << std::endl;
}

auto DropDataProvider::loadDrops() -> void {
	m_dropInfo.clear();
	DropInfo drop;
	int32_t dropper;

	auto dropFlags = [&drop](const opt_string_t &flags) {
		StringUtilities::runFlags(flags, [&drop](const string_t &cmp) {
			if (cmp == "is_mesos") drop.isMesos = true;
		});
	};

	soci::session &sql = Database::getDataDb();
	soci::rowset<> rs = (sql.prepare << "SELECT * FROM drop_data");

	for (const auto &row : rs) {
		drop = DropInfo();

		dropper = row.get<int32_t>("dropperid");
		drop.itemId = row.get<int32_t>("itemid");
		drop.minAmount = row.get<int32_t>("minimum_quantity");
		drop.maxAmount = row.get<int32_t>("maximum_quantity");
		drop.questId = row.get<int16_t>("questid");
		drop.chance = row.get<uint32_t>("chance");
		dropFlags(row.get<opt_string_t>("flags"));

		m_dropInfo[dropper].push_back(drop);
	}

	rs = (sql.prepare << "SELECT * FROM user_drop_data ORDER BY dropperid");
	int32_t lastDropperId = -1;
	bool dropped = false;

	for (const auto &row : rs) {
		drop = DropInfo();

		dropper = row.get<int32_t>("dropperid");
		drop.itemId = row.get<int32_t>("itemid");
		drop.minAmount = row.get<int32_t>("minimum_quantity");
		drop.maxAmount = row.get<int32_t>("maximum_quantity");
		drop.questId = row.get<int16_t>("questid");
		drop.chance = row.get<uint32_t>("chance");
		dropFlags(row.get<opt_string_t>("flags"));

		if (dropper != lastDropperId) {
			dropped = false;
		}
		if (!dropped && m_dropInfo.find(dropper) != std::end(m_dropInfo)) {
			m_dropInfo.erase(dropper);
			dropped = true;
		}
		m_dropInfo[dropper].push_back(drop);
		lastDropperId = dropper;
	}
}

auto DropDataProvider::loadGlobalDrops() -> void {
	m_globalDrops.clear();
	GlobalDrop drop;

	soci::rowset<> rs = (Database::getDataDb().prepare << "SELECT * FROM drop_global_data");

	for (const auto &row : rs) {
		drop = GlobalDrop();

		drop.continent = row.get<int8_t>("continent");
		drop.itemId = row.get<int32_t>("itemid");
		drop.minAmount = row.get<int16_t>("minimum_quantity");
		drop.maxAmount = row.get<int16_t>("maximum_quantity");
		drop.minLevel = row.get<uint8_t>("minimum_level");
		drop.maxLevel = row.get<uint8_t>("maximum_level");
		drop.questId = row.get<int16_t>("questid");
		drop.chance = row.get<uint32_t>("chance");
		StringUtilities::runFlags(row.get<opt_string_t>("flags"), [&drop](const string_t &cmp) {
			if (cmp == "is_mesos") drop.isMesos = true;
		});

		m_globalDrops.push_back(drop);
	}
}