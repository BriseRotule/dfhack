#include "Core.h"
#include "Console.h"
#include "PluginManager.h"

#include "DataDefs.h"
#include "df/world.h"
#include "df/report.h"
#include "df/announcement_type.h"

using std::string;
using std::vector;

using namespace DFHack;
//using namespace df::enums;

using df::global::world;

DFHACK_PLUGIN("combatLog");

command_result combatLog (color_ostream &out, vector <string> & parameters)
{
	out.print("Report number :  %d.\n", world->status.reports.size());


	for (size_t i = 0; i < world->status.reports.size(); i++)
	{
		df::report *current=world->status.reports[i];
		//switch (current->type){
		//	case df::announcement_type.COMBAT_TWIST_WEAPON:
		//	case df::announcement_type.COMBAT_LET_ITEM_DROP:
		//	case df::announcement_type.COMBAT_START_CHARGE:
		//	case df::announcement_type.COMBAT_SURPRISE_CHARGE:
		//	case df::announcement_type.COMBAT_JUMP_DODGE_PROJ:
		//	case df::announcement_type.COMBAT_JUMP_DODGE_STRIKE:
		//	case df::announcement_type.COMBAT_DODGE:
		//	case df::announcement_type.COMBAT_COUNTERSTRIKE:
		//	case df::announcement_type.COMBAT_BLOCK:
		//	case df::announcement_type.COMBAT_PARRY:
		//	case df::announcement_type.COMBAT_CHARGE_COLLISION:
		//	case df::announcement_type.COMBAT_CHARGE_DEFENDER_TUMBLES:
		//	case df::announcement_type.COMBAT_CHARGE_DEFENDER_KNOCKED_OVER:
		//	case df::announcement_type.COMBAT_CHARGE_ATTACKER_TUMBLES:
		//	case df::announcement_type.COMBAT_CHARGE_ATTACKER_BOUNCE_BACK:
		//	case df::announcement_type.COMBAT_CHARGE_TANGLE_TOGETHER:
		//	case df::announcement_type.COMBAT_CHARGE_TANGLE_TUMBLE:
		//	case df::announcement_type.COMBAT_CHARGE_RUSH_BY:
		//	case df::announcement_type.COMBAT_CHARGE_MANAGE_STOP:
		//	case df::announcement_type.COMBAT_CHARGE_OBSTACLE_SLAM:
		//	case df::announcement_type.COMBAT_WRESTLE_LOCK:
		//	case df::announcement_type.COMBAT_WRESTLE_CHOKEHOLD:
		//	case df::announcement_type.COMBAT_WRESTLE_TAKEDOWN:
		//	case df::announcement_type.COMBAT_WRESTLE_THROW:
		//	case df::announcement_type.COMBAT_WRESTLE_RELEASE_LOCK:
		//	case df::announcement_type.COMBAT_WRESTLE_RELEASE_CHOKE:
		//	case df::announcement_type.COMBAT_WRESTLE_RELEASE_GRIP:
		//	case df::announcement_type.COMBAT_WRESTLE_STRUGGLE:
		//	case df::announcement_type.COMBAT_WRESTLE_RELEASE_LATCH:
		//	case df::announcement_type.COMBAT_WRESTLE_STRANGLE_KO:
		//	case df::announcement_type.COMBAT_WRESTLE_ADJUST_GRIP:
		//	case df::announcement_type.COMBAT_GRAB_TEAR:
		//	case df::announcement_type.COMBAT_STRIKE_DETAILS:
		//	case df::announcement_type.COMBAT_STRIKE_DETAILS_2:
		//	case df::announcement_type.COMBAT_EVENT_ENRAGED:
		//	case df::announcement_type.COMBAT_EVENT_STUCKIN:
		//	case df::announcement_type.COMBAT_EVENT_LATCH_BP:
		//	case df::announcement_type.COMBAT_EVENT_LATCH_GENERAL:
		//	case df::announcement_type.COMBAT_EVENT_PROPELLED_AWAY:
		//	case df::announcement_type.COMBAT_EVENT_KNOCKED_OUT:
		//	case df::announcement_type.COMBAT_EVENT_STUNNED:
		//	case df::announcement_type.COMBAT_EVENT_WINDED:
		//	case df::announcement_type.COMBAT_EVENT_NAUSEATED:
		//		out.print(current->text.c_str());
		//		out.print("Type : %d",current->type);
		//		out.print("\n");
		//		break;
		//	default:
		//		break;
		//}
		out.print(current->text.c_str());
		out.print(" - Type : %d",current->type);
		out.print("\n");
	}

    return CR_OK;
}

DFhackCExport command_result plugin_init ( color_ostream &out, vector <PluginCommand> &commands)
{
    commands.push_back(PluginCommand("combatLog","Display current combat log.",combatLog));
    return CR_OK;
}
