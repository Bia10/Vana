/*
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
*/
#pragma once

#define CMSG_PLAYER_LOAD 0x14

#define CMSG_MAP_CHANGE 0x25
#define CMSG_CHANNEL_CHANGE 0x26
#define CMSG_CASH_SHOP 0x27
#define CMSG_PLAYER_MOVE 0x28
#define CMSG_CHAIR 0x29
#define CMSG_USE_CHAIR 0x2a
#define CMSG_ATTACK_MELEE 0x2b
#define CMSG_ATTACK_RANGED 0x2c
#define CMSG_ATTACK_MAGIC 0x2d
#define CMSG_ATTACK_ENERGY_CHARGE 0x2e
#define CMSG_PLAYER_DAMAGE 0x2f
#define CMSG_PLAYER_CHAT 0x30
#define CMSG_CHALKBOARD 0x31
#define CMSG_EMOTE 0x32
#define CMSG_ITEM_EFFECT 0x33
#define CMSG_UPGRADE_TOMB_EFFECT 0x34
// 0x35 does not exist?
// 0x36 does not exist?
#define CMSG_BAN_MAP_BY_MOB 0x37 // int mapmobid; Triggered when mobs with banType == 1 hit you (for example, 9300160).
#define CMSG_MONSTER_BOOK 0x38
#define CMSG_NPC_TALK 0x39
#define CMSG_REMOTE_MERCHANT_OPEN 0x3a // For 'Store Remote Controller', 5470000
#define CMSG_NPC_TALK_CONT 0x3b // i.e. clicking next on NPC
#define CMSG_SHOP 0x3c
#define CMSG_STORAGE 0x3d
#define CMSG_MERCHANT 0x3e
#define CMSG_STORE_BANK 0x3f // For Fredrick / store bank responses
#define CMSG_DUEY 0x40
#define CMSG_SHOP_SCANNER 0x41
#define CMSG_SHOP_LINK 0x42 // int ?, int ?
#define CMSG_ADMIN_SHOP 0x43
#define CMSG_INVENTORY_SLOT_MERGER 0x44 // int ticks, byte inventory
#define CMSG_INVENTORY_SLOT_SORTER 0x45 // int ticks, byte inventory; Also known as 'gather'. It should be a little icon with three dashes (burger), but isnt rendered nor usable
#define CMSG_ITEM_MOVE 0x46
#define CMSG_ITEM_USE 0x47
#define CMSG_ITEM_CANCEL 0x48
#define CMSG_HEAL_BY_CHAIR 0x49 // Sent when you sit on a chair that heals you
#define CMSG_SUMMON_BAG_USE 0x4a
#define CMSG_PET_FOOD_USE 0x4b
#define CMSG_MOUNT_FOOD_USE 0x4c // int ticks, short slot, int itemid; Item 2260000
#define CMSG_USE_SCRIPT_ITEM 0x4d // For items that runs scripts
#define CMSG_CASH_ITEM_USE 0x4e
#define CMSG_DESTROY_PET_ITEM 0x4f // int ticks, long cashid; Sent when you try to open up a dead 'trail' pet, like the snail.
#define CMSG_USE_BRIDLE_ITEM 0x50 // int ticks, short slot, int itemid, int mapmobid; Sent when using a bridle item (227000 and higher)
#define CMSG_SKILLBOOK_USE 0x51
#define CMSG_OWL_OF_MINERVA_USE 0x52 // byte slot; Sent when you open up the Owl of Minerva use item (2310000)
#define CMSG_TELEPORT_ROCK_USE 0x53 // Only the one in your Use
#define CMSG_TOWN_SCROLL_USE 0x54
#define CMSG_SCROLL_USE 0x55
#define CMSG_STAT_ADDITION 0x56
#define CMSG_MULTI_STAT_ADDITION 0x57 // The auto-assign button
#define CMSG_PLAYER_HEAL 0x58
#define CMSG_SKILL_ADD 0x59
#define CMSG_SKILL_USE 0x5a
#define CMSG_SKILL_CANCEL 0x5b
#define CMSG_SPECIAL_SKILL 0x5c // Chakra, Pierce, Monster Magnet, Big Bang
#define CMSG_DROP_MESOS 0x5d
#define CMSG_FAME 0x5e
// Doesn't exist?
#define CMSG_PLAYER_INFO 0x60
#define CMSG_PET_SUMMON 0x61
#define CMSG_CHECK_TEMPORARY_STAT_DURATION 0x62 // If you have temporary stats applied, the client will send this packet
#define CMSG_MAP_CHANGE_SPECIAL 0x63
#define CMSG_MAP_TELEPORT 0x64
#define CMSG_TELEPORT_ROCK 0x65
#define CMSG_USE_LIE_DETECTOR_ITEM 0x66 // string name, short slot, int itemid
#define CMSG_USE_LIE_DETECTOR_SKILL 0x67 // string name
#define CMSG_LIE_DETECTOR_RESPONSE 0x68 // string response
#define CMSG_CLAIM_REQUEST 0x69 // bool include_chatlog, string target_player, byte type, string context, if (include_chatlog) { string chatlog }
#define CMSG_QUEST_OBTAIN 0x6a
#define CMSG_BUFF_ACKNOWLEDGE 0x6b
#define CMSG_BOMB_SKILL_USE 0x6c
#define CMSG_MACRO_LIST 0x6d
#define CMSG_USE_ITEM_NPC_REQUEST 0x6e // ushort slot, int itemid; Used for items in category 545 and 239. However, there's no item that can do this (239 does not exist)
#define CMSG_USE_REWARD_ITEM 0x6f
#define CMSG_MAKE_ITEM 0x70 // Using item maker skill

#define CMSG_OPEN_TREASURE_CHEST 0x72 // short slot, int itemid; Items 4280000 and up
#define CMSG_USE_REMOTE_GACHAPON_TICKET 0x73 // int itemid, int index; Sent when clicking one of the 10 buttons in the UI
#define CMSG_ADMIN_BROADCAST 0x74 // Commands like '/alertall'
#define CMSG_MESSAGE_GROUP 0x75 // Party, buddy and guild chat
#define CMSG_COMMAND 0x76 // / commands like "/find"
#define CMSG_COUPLE_CHAT 0x77 // string ???, string message
#define CMSG_PLAYER_CHATROOM 0x78 // Messenger system
#define CMSG_PLAYER_ROOM 0x79 // Trades, player shops, minigames, etc.
#define CMSG_PARTY 0x7a
#define CMSG_PARTY_RESPONSE 0x7b // Like blocked invites and such
#define CMSG_GUILD 0x7c
#define CMSG_GUILD_RESPONSE 0x7d
#define CMSG_ADMIN_COMMAND 0x7e
#define CMSG_ADMIN_COMMAND_LOG 0x7f // '/(command) (parameters)'
#define CMSG_BUDDY 0x80
#define CMSG_SEND_NOTE 0x81
// 0x82 does not exist?
#define CMSG_MYSTIC_DOOR_ENTRY 0x83
#define CMSG_SLIDE_MESSAGE 0x84 // byte value
#define CMSG_KEYMAP 0x85
#define CMSG_ROCK_PAPER_SCISSOR 0x86
#define CMSG_ENGAGEMENT_REQUEST 0x87
#define CMSG_FREDRICK_STORAGE 0x88
#define CMSG_WEDDING 0x89
#define CMSG_WEDDING_BLESS 0x8a
#define CMSG_BOOBY_TRAP_ALERT 0x8b // int trap_type; anti hack measure for itemvac
#define CMSG_STALK_BEGIN 0x8c // Click on yourself in the minimap, and you'll send this packet.
#define CMSG_ALLIANCE 0x8d
#define CMSG_ALLIANCE_DENIED 0x8e
#define CMSG_FAMILY_TREE 0x8f
#define CMSG_FAMILY_WINDOW_TOP 0x90
#define CMSG_FAMILY_ADD 0x91
#define CMSG_FAMILY_DELETE_JUNIOR 0x92 // + juniorid
#define CMSG_FAMILY_DELETE_SENIOR 0x93
#define CMSG_FAMILY_ANSWER 0x94
#define CMSG_FAMILY_BUFF 0x95
#define CMSG_FAMILY_PRECEPT 0x96
#define CMSG_FAMILY_ASK_WARP 0x97
// 0x98 does not exist
#define CMSG_BBS 0x99
#define CMSG_MTS 0x9a
#define CMSG_MOB_CRC_KEY_CHANGED_REPLY 0x9b
#define CMSG_USE_EXP_UP_ITEM 0x9c // int tickcount, short pos, int itemid
#define CMSG_USE_TEMP_EXP_UP_ITEM 0x9d // int tickcount
#define CMSG_USE_NEWYEAR_CARD 0x9e // byte, short, int, string, string
#define CMSG_BUFF_ITEM_USE 0x9f
// 0xa0 does not exist (begin pet)
#define CMSG_PET_MOVEMENT 0xa1
#define CMSG_PET_CHAT 0xa2
#define CMSG_PET_COMMAND 0xa3
#define CMSG_PET_LOOT 0xa4
#define CMSG_PET_CONSUME_POTION 0xa5
#define CMSG_PET_UPDATE_EXCEPTION_LIST 0xa6
// 0xa7 does not exist (end pet)
// 0xa8 does not exist (begin summon)
#define CMSG_SUMMON_MOVEMENT 0xa9
#define CMSG_SUMMON_ATTACK 0xaa
#define CMSG_SUMMON_DAMAGE 0xab
#define CMSG_SUMMON_SKILL 0xac
// 0xad does not exist (end summon)
// 0xae does not exist (end user)
// 0xaf does not exist (begin field)
// 0xb0 does not exist (begin lifepool)
// 0xb1 does not exist (begin mob)
#define CMSG_MOB_CONTROL 0xb2
#define CMSG_PLAYER_MOB_DISTANCE 0xb3
#define CMSG_MOB_LOOT 0xb4 // int mapmobid, int mapitemid
#define CMSG_MOB_COLLISION 0xb5 // int mapmobid, int damage; possible exploit?
#define CMSG_FRIENDLY_MOB_DAMAGE 0xb6
#define CMSG_MOB_EXPLOSION 0xb7
#define CMSG_MOB_TURNCOAT_DAMAGE 0xb8 // For Hypnotize
// 0xb9 does not exist (end mob)
// 0xba does not exist (begin npc)
#define CMSG_NPC_ANIMATE 0xbb
#define CMSG_NPC_REQUEST_SPECIAL_ACTION 0xbc // int mapnpcid, string effect; Say 'Maple's the bomb!' in range of Gaga (90000021) to sent
// 0xbd does not exist (end npc)
// 0xbe does not exist (end lifepool)
// 0xbf does not exist (begin droppool)
#define CMSG_ITEM_LOOT 0xc0
// 0xc1 does not exist (end droppool)
// 0xc2 does not exist (begin reactorpool)
#define CMSG_REACTOR_HIT 0xc3
#define CMSG_REACTOR_TOUCH 0xc4
#define CMSG_RESET_NLCPQ 0xc5 // Send on field init. Not sure why, probably an ugly hack. Exists in v.95 and appeared around v.75
// 0xc6 does not exist (end reactorpool)
// 0xc7 does not exist (begin event field)
#define CMSG_EVENT_START 0xc8 // Sent when admin uses /start
#define CMSG_PLAYER_BOAT_MAP 0xd2 // Packet format [map ID:4] [?:1], seems like this gets sent when a player spawns on a boat map, the ? I got was never anything other than 0

#define CMSG_PARTY_SEARCH_START 0xd4 // int min_level, int max_level, int max_players, int jobflags
#define CMSG_PARTY_SEARCH_STOP 0xd5


#define CMSG_CASHSHOP_CHECK_CASH 0xda

#define CMSG_CASHSHOP_REDEEM_COUPON 0xdc
#define CMSG_CASHSHOP_OPERATION 0xdb

#define CMSG_ADMIN_MESSENGER 0xeb

// 0xf7 does not exist (begin hammer)
#define CMSG_HAMMER 0xf8
#define CMSG_HAMMER_COMPLETE 0xf9
// 0xfa does not exist (end hammer)
