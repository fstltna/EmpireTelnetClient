/*
 *  Empire - A multi-player, client/server Internet based war game.
 *  Copyright (C) 1986-2017, Dave Pare, Jeff Bailey, Thomas Ruschak,
 *                Ken Stevens, Steve McClure, Markus Armbruster
 *
 *  Empire is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  ---
 *
 *  See files README, COPYING and CREDITS in the root of the source
 *  tree for related information and legal notices.  It is expected
 *  that future projects/authors will amend these files as needed.
 *
 *  ---
 *
 *  empmod.c: List all commands for Empire
 *
 *  Known contributors to this file:
 *     Dave Pare, 1986
 *     Jeff Bailey
 *     Thomas Ruschak, 1992
 *     Ken Stevens, 1995
 *     Steve McClure, 1996-2000
 *     Markus Armbruster, 2004-2015
 */

/*
 * Fun fact: named empmod for historical reasons --- Empire used to be
 * broken into seven modules on the venerable PDP-11 so it could fit
 * in 64k I/D space.
 */

#include <config.h>

#include "com.h"
#include "player.h"
#include "prototypes.h"
#include "testing.h"

struct cmndstr player_coms[] = {
/*  command form                       cost	addr    permit */
    {"accept  [as-COUNTRY]", 0, acce, C_MOD, NORM},
    {"add <NAT> <NAME> <REP> <STATUS>", 0, add, C_MOD, GOD},
    {"announce", 0, tele, C_MOD, 0},
    {"anti <SECTS>", 3, anti, C_MOD, NORM + MONEY + CAP},
    {"apropos <topic>", 0, apro, 0, 0},
    {"arm <PLANE> <NUKE> <airburst?>", 3, arm, C_MOD, NORM + CAP},
    {"army <ARMY> <UNITS>", 0, army, C_MOD, NORM},
    {"assault <to-SECT> <from-SHIP> [<forts?> <ships?> <arty?> <planes?>]",
     3, assa, C_MOD, NORM + MONEY + CAP},
    {"attack <SECT> [<forts?> <ships?> <arty?> <planes?>]",
     3, atta, C_MOD, NORM + MONEY + CAP},
    {"bdes <SECTS> <type>", 0, bdes, C_MOD, NORM},
    {"bestpath <SECTS> <SECTS>", 0, best, 0, NORM},
    {"bmap <SECTS|SHIP> [s|l|n|p|r|t|*|h]", 0, map, C_MOD, NORM},
    {"board <to-SHIP> [<from-SHIP>|<from-sector>]",
     3, boar, C_MOD, NORM + MONEY + CAP},
    {"bomb <bomber-PLANES> <fighter-PLANES> <pin|strat> <ap-SECT> <PATH|DESTINATION>",
     2, bomb, C_MOD, NORM + MONEY + CAP},
    {"break", 0, brea, C_MOD, SANCT},
    {"budget", 1, budg, 0, NORM},
    {"build <s|l|b|p|n|t> <SECTS> <type|dir> [<number> <tech> <sure?>]",
     1, buil, C_MOD, NORM + MONEY + CAP},
    {"buy <COMM> <LOT#> <BID/UNIT> <DEST>",
     1, buy, C_MOD, NORM + MONEY + CAP},
    {"bye", 0, quit, 0, 0},
    {"capital <SECT>", 0, capi, C_MOD, NORM},
    {"cargo <SHIPS>", 0, carg, 0, NORM},
    {"census <SECTS>", 0, cens, 0, NONVIS},
    {"change <country|representative> <NAME>", 0, chan, C_MOD, NONVIS},
    {"coastwatch <SECTS>", 1, coas, C_MOD, NORM + CAP},
    {"collect <LOAN> <SECT>", 2, coll, C_MOD, NORM + MONEY + CAP},
    {"commodity <SECTS>", 0, comm, 0, NONVIS},
    {"consider <loan> <LOAN> <acc|decl|post>",
     1, cons, C_MOD, NORM + CAP},
    {"convert <SECTS> <NUM>", 2, conv, C_MOD, NORM + MONEY + CAP},
    {"country <NATS>", 0, coun, 0, 0},
    {"cutoff <SECTS>", 0, cuto, 0, NORM},
    {"declare <all|friend|neut|hos|war> <NATS>",
     2, decl, C_MOD, NORM + CAP},
    {"deliver <COMM> <SECTS> [q|<THRESH>] [<DIR>]", 1, deli, C_MOD, NORM},
    {"demobilize <SECTS> <NUM> <active-reserve?>", 1, demo, C_MOD,
     NORM + MONEY + CAP},
    {"designate <SECTS> <type>", 1, desi, C_MOD, NORM},
    {"disable", 0, disa, C_MOD, GOD},
    {"disarm <PLANE>", 2, disarm, C_MOD, NORM + CAP},
    {"distribute <SECTS> <DISTSECT|.|h>", 1, dist, C_MOD, NORM},
    {"drop <cargo-PLANES> <fighter-PLANES> <ap-SECT> <PATH|DESTINATION> <COMM>",
     1, drop, C_MOD, NORM + MONEY + CAP},
    {"dump <SECTS> [<fields>]", 0, dump, 0, NORM},
    {"echo [<string>]", 0, echo, 0, 0},
    {"edit <l|s|p|u|n|c> <SECTS|SHIPS|PLANES|LANDS|NUKES|NATS> [<KEY> <VALUE>]...",
     0, edit, C_MOD, GOD},
    {"enable", 0, enab, C_MOD, GOD},
    {"enlist <SECTS> <NUM>", 2, enli, C_MOD, NORM + MONEY + CAP},
    {"execute <INPUT FILE>", 0, execute, 0, EXEC},
    {"explore <c|m> <SECT> <NUM> <PATH|DESTINATION>",
     1, explore, C_MOD, NORM + MONEY + CAP},
    {"financial", 0, fina, 0, 0},
    {"fire <TYPE> <from-SECTS | SHIPS | UNITS> [TO-SECT | SHIP]",
     1, multifire, C_MOD, NORM + MONEY + CAP},
    {"flash <COUNTRY> [<message>]", 0, flash, 0, 0},
    {"fleetadd <FLEET> <SHIPS>", 0, flee, C_MOD, NORM},
    {"fly <cargo-PLANES> <fighter-PLANES> <ap-SECT> <PATH|DESTINATION> <COM>",
     2, fly, C_MOD, NORM + MONEY + CAP},
    {"force", 0, force, C_MOD, GOD},
    {"fortify <UNITS> <MOB>", 1, fort, C_MOD, NORM + CAP},
    {"give <COMM> <SECTS> <NUM>", 0, give, C_MOD, GOD},
    {"grind <SECTS> <NUM>", 1, grin, C_MOD, NORM + MONEY + CAP},
    {"harden <PLANES> <NUM>", 2, hard, C_MOD, NORM + MONEY + CAP},
    {"headlines [days]", 0, head, 0, 0},
    {"help <topic>", 0, info, 0, 0},
    {"improve <road|rail|defense> <SECTS> <NUM>",
     1, improve, C_MOD, NORM + MONEY + CAP},
    {"info <topic>", 0, info, 0, 0},
    {"land <UNITS>", 0, land, 0, NORM},
    {"launch <PLANES> <SECT|SHIP>", 3, laun, C_MOD, NORM + MONEY + CAP},
    {"lbmap <SECTS|LAND UNIT> [s|l|n|p|r|t|*|h]", 0, map, C_MOD, NORM},
    {"lboard <to-LAND> [<from-sector>]",
     3, lboa, C_MOD, NORM + MONEY + CAP},
    {"lcargo <UNITS>", 0, lcarg, 0, NORM},
    {"ldump <UNITS> [<fields>]", 0, ldump, 0, NORM},
    {"ledger <LOANS>", 0, ledg, 0, NORM},
    {"level <SECTS>", 0, leve, 0, NORM},
    {"list", 0, explain, 0, 0},
    {"lload <COMM|\"land\"|\"plane\"> <UNITS> <NUM|UNITS|PLANES>",
     1, lload, C_MOD, NORM + CAP},
    {"llookout <UNITS>", 1, llook, 0, NORM + CAP},
    {"lmap <SECTS|LAND UNIT> [s|l|n|p|*|h]", 0, map, C_MOD, NORM},
    {"lmine <UNITS>", 2, landmine, C_MOD, NORM + MONEY + CAP},
    {"load <COMM|\"land\"|\"plane\"> <SHIPS> <NUM|UNITS|PLANES>",
     1, load, C_MOD, NORM + CAP},
    {"lookout <SHIPS>", 1, look, 0, NORM + CAP},
    {"lost", 0, lost, 0, NORM},
    {"lradar <UNITS | SECTS>", 1, lrad, C_MOD, NORM + CAP},
    {"lretreat <UNITS|ARMY> [q | <PATH> <i|h|b|c>]",
     1, lretr, C_MOD, NORM + CAP},
    {"lstat <UNITS>", 0, lsta, 0, NORM},
    {"ltend <COMM> <tender-SHIPS> <NUM> <UNITS>",
     1, ltend, C_MOD, NORM + CAP},
    {"lunload <COMM|\"land\"|\"plane\"> <UNITS> <NUM|UNITS|PLANES>",
     1, lload, C_MOD, NORM + CAP},
    {"map <SECTS|SHIP> [s|l|n|p|*|h]", 0, map, C_MOD, NORM},
    {"march <UNITS> <PATH|DESTINATION>", 1, march, C_MOD, NORM + CAP},
    {"market <COMM|\"all\">", 0, mark, C_MOD, NORM},
    {"mine <SHIPS>", 2, mine, C_MOD, NORM + MONEY + CAP},
    {"mission <TYPE> <PLANES|SHIPS|UNITS> <mission type> <op sect> [<radius>]",
     2, mission, C_MOD, NORM + CAP},
    {"morale <UNITS> <retreat%>", 1, morale, C_MOD, NORM + CAP},
    {"motd", 0, show_motd, 0, 0},
    {"move <COMM> <SECT> <NUM> <PATH|DESTINATION>",
     1, move, C_MOD, NORM + CAP},
    {"name <SHIPS> <NAME>", 0, name, C_MOD, NORM},
    {"nation [as-COUNTRY]", 0, nati, 0, 0},
    {"navigate <SHIPS> <PATH|DESTINATION>", 1, navi, C_MOD, NORM + CAP},
    {"nbmap <SECTS|NUKE> [s|l|n|p|r|t|*|h]", 0, map, C_MOD, NORM},
    {"ndump <NUKES>", 0, ndump, 0, NORM},
    {"newcap <NAT> <SECTOR>", 0, new, C_MOD, GOD},
    {"neweff <SECTS>", 0, newe, 0, NORM},
    {"newspaper [days]", 0, news, 0, 0},
    {"nmap <SECTS|NUKE> [s|l|n|p|*|h]", 0, map, C_MOD, NORM},
    {"nuke <NUKES>", 0, nuke, 0, NORM},
    {"offer <loan> <NAT> [<NUM> <DAYS> <IRATE>]",
     1, offe, C_MOD, NORM + MONEY + CAP},
    {"origin <SECT|COUNTRY|~>", 1, orig, C_MOD, NORM},
    {"paradrop <cargo-PLANES> <fighter-PLANES> <ap-SECT> <PATH|DESTINATION>",
     3, para, C_MOD, NORM + MONEY + CAP},
    {"path <SECT>", 0, path, C_MOD, NORM},
    {"payoff <SHIPS>", 0, payo, 0, NORM},
    {"pbmap <SECTS|PLANE> [s|l|n|p|r|t|*|h]", 0, map, C_MOD, NORM},
    {"pboard <PLANES>", 3, pboa, C_MOD, NORM + MONEY + CAP},
    {"pdump <PLANES> [<fields>]", 0, pdump, 0, NORM},
    {"peek <SECTS>", 0, peek, 0, GOD},
    {"plane <SECTS>", 0, plan, 0, NORM},
    {"players", 0, play, 0, 0},
    {"pmap <SECTS|PLANE> [s|l|n|p|*|h]", 0, map, C_MOD, NORM},
    {"power [\"new\"|\"update\"] [<NUMBER OF COUNTRIES> | \"country\" <NATS>]",
     0, powe, C_MOD, 0},
    {"pray", 0, tele, C_MOD, NORM},
    {"production <SECTS>", 0, prod, 0, NORM},
    {"pstat <PLANES>", 0, pstat, 0, NORM},
    {"quit", 0, quit, 0, 0},
    {"radar <SHIPS | SECTS>", 1, rada, C_MOD, NORM + CAP},
    {"range <PLANES> <range>", 1, range, C_MOD, NORM + CAP},
    {"read [yes|no|<CNUM/CNAME>]", 0, rea, C_MOD, NONVIS},
    {"realm <number> [<SECTS>]", 0, real, C_MOD, NORM},
    {"recon <spy-PLANES> <fighter-PLANES> <ap-SECT> <PATH|DESTINATION>",
     3, reco, C_MOD, NORM + MONEY + CAP},
    {"reject <reject|accept> <announcements|mail|loans> <NAT>",
     2, reje, C_MOD, NORM},
    {"relations  [as-COUNTRY]", 0, rela, 0, 0},
    {"reload", 0, relo, C_MOD, GOD},
    {"repay <LOAN> <NUM>", 1, repa, C_MOD, NORM + MONEY + CAP},
    {"report <NATS>", 0, repo, 0, 0},
    {"reset <lot #> <0|price>", 1, rese, C_MOD, NORM + CAP},
    {"resource <SECTS>", 0, reso, 0, NONVIS},
    {"retreat <SHIPS|FLEET> [q | <PATH> <i|t|s|h|b|d|u|c>]",
     1, retr, C_MOD, NORM + CAP},
    {"route <COMM> <SECTS>", 1, rout, C_MOD, NORM},
    {"sabotage <UNITS>", 1, sabo, C_MOD, NORM + MONEY + CAP},
    {"satellite <PLANE> [<se|sh|l> [?cond&cond&...]]",
     1, sate, C_MOD, NORM + CAP},
    {"sbmap <SECTS|SHIP> [s|l|n|p|r|t|*|h]", 0, map, C_MOD, NORM},
    {"scrap <s|p|l> <SHIPS|PLANES|UNITS>",
     2, scra, C_MOD, NORM + MONEY + CAP},
    {"scuttle <s|p|l> <SHIPS|PLANES|UNITS>", 5, scut, C_MOD, NORM + CAP},
    {"sdump <SHIPS> [<fields>]", 0, sdump, 0, NORM},
    {"sect <SECTS>", 0, sct, C_MOD, NORM},
    {"sell <COMM> <SECTS> <NUM> <NUM>", 1, sell, C_MOD, NORM + CAP},
    {"set <TYPE> <SHIPS|PLANES|UNITS|NUKES> <PRICE>",
     1, set, C_MOD, NORM + CAP},
    {"setresource <type> <SECTS> <NUM>", 0, setres, C_MOD, GOD},
    {"setsector <type> <SECTS> <NUM>", 0, setsector, C_MOD, GOD},
    {"sharebmap <CNUM/CNAME> <SECTS> [<des>]", 0, shar, C_MOD, NORM},
    {"shark <LOAN>", 25, shark, C_MOD, NORM + MONEY + CAP},
    {"ship <SHIPS>", 0, shi, 0, NORM},
    {"shoot <c|u> <SECTS> <NUMBER>", 3, shoo, C_MOD, NORM + MONEY + CAP},
    {"show <TYPE> <\"build\"|\"stats\"|\"cap\"> [<tech>]\n"
     "\tshow <bridge|item|news|product|tower>\n"
     "\tshow updates [<NUM>]>",
     0, show, 0, 0},
    {"shutdown <minutes> <disable update?>", 0, shut, 0, GOD},
    {"sinfrastructure <SECTS>", 0, sinfra, 0, NONVIS},
    {"skywatch <SECTS>", 1, skyw, C_MOD, NORM + CAP},
    {"smap <SECTS|SHIP> [s|l|n|p|*|h]", 0, map, C_MOD, NORM},
    {"sonar <SHIPS> <brief?>", 1, sona, C_MOD, NORM + CAP},
    {"spy <SECTS>", 1, spy, C_MOD, NORM + CAP},
    {"sstat <SHIPS>", 0, sstat, 0, NORM},
    {"start <TYPE> <SECTS|PLANES|SHIPS|UNITS|NUKES>", 1, start, C_MOD, NORM},
    {"starvation [<SECTS>|l <UNITS>|s <SHIPS>]", 0, starve, 0, NORM},
    {"stockpile <STOCKPILE> <NUKES>", 0, stoc, C_MOD, NORM},
    {"stop <TYPE> <SECTS|PLANES|SHIPS|UNITS|NUKES>", 1, stop, C_MOD, NORM},
    {"strength <SECTS>", 1, stre, C_MOD, NORM},
    {"supply <LAND UNITS>", 1, supp, C_MOD, NORM + CAP},
    {"survey <SELECTOR> <SECTS>", 0, surv, C_MOD, NORM},
    {"swapsector <SECT> <SECT>", 0, swaps, C_MOD, GOD},
    {"sweep <sweep-PLANES> <fighter-PLANES> <ap-SECT> <PATH|DESTINATION>",
     3, reco, C_MOD, NORM + MONEY + CAP},
    {"telegram <NATS>...", 0, tele, C_MOD, NORM},
    {"tend <COMM|\"land\"> <tender-SHIPS> <NUM|UNIT> <dest-SHIPS>",
     1, tend, C_MOD, NORM + CAP},
    {"territory <SECTS> <NUMBER> [<FIELD>]", 0, terr, C_MOD, NORM},
    {"test <COMM> <SECT> <NUM> <PATH|DESTINATION>",
     1, move, C_MOD, NORM},
    {"threshold <COMM> <SECTS> <THRESH>", 1, thre, C_MOD, NORM},
    {"toggle [inform|flash|beep|coastwatch|sonar|techlists] [on|off]",
     0, togg, C_MOD, 0},
    {"torpedo <submarine-SHIPS> <target-SHIP>",
     3, torp, C_MOD, NORM + MONEY + CAP},
    {"trade", 1, trad, C_MOD, NORM + MONEY + CAP},
    {"transport <\"nuke\"|\"plane\"> <NUKES|PLANES> <PATH|DESTINATION>",
     1, tran, C_MOD, NORM + CAP},
    {"turn <\"on\"|\"off\"|\"mess\">", 0, turn, C_MOD, GOD},
    {"unload <COMM|\"land\"|\"plane\"> <SHIPS> <NUM|UNIT|PLANE>",
     1, load, C_MOD, NORM + CAP},
    {"update", 0, upda, 0, 0},
    {"upgrade <s|p|l> <SHIPS|PLANES|UNITS>",
     1, upgr, C_MOD, NORM + MONEY + CAP},
    {"version", 0, vers, 0, 0},
    {"wall [<message>]", 0, wall, 0, NORM},
    {"wingadd <WING> <PLANES>", 0, wing, C_MOD, NORM},
    {"wipe <SECTS>", 1, wipe, C_MOD, NORM},
    {"wire [yes|no|<days>]", 0, rea, C_MOD, 0},
    {"work <LAND UNITS> <AMOUNT>", 1, work, C_MOD, NORM + MONEY + CAP},
    {"xdump [\"meta\"] <TYPE> [<RECORDS>]", 0, xdump, 0, 0},
    {"zdone <y|n|c>", 0, zdon, C_MOD, NORM},
    {"__cmd \"added\" <NUM> <NUM> <NUM>", 0, testing_cmd, 0, TESTING},
    {NULL, 0, NULL, 0, 0}
};