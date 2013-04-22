#include "Core.h"
#include "Console.h"
#include "PluginManager.h"

#include "DataDefs.h"
#include "df/world.h"
#include "df/report.h"
#include "df/announcement_type.h"
#include "df/unit.h"
#include "df/language_name.h"

using std::string;
using std::vector;

using namespace DFHack;
using namespace df::enums;

using df::global::world;

DFHACK_PLUGIN("combatLog");
void printReport(color_ostream &out,std::vector<df::report*> reports);
int32_t relateReport(int32_t refReport,std::vector<df::report*> reports);


command_result combatLog (color_ostream &out, vector <string> & parameters)
{
	std::vector<df::report*> combatLog;

	int unitReportCounter=0;

	out.print("\n\nall units : %d.\n",world->units.all.size());
	for (size_t i = 0; i < world->units.all.size(); i++)
	{
		df::unit *unit=world->units.all[i];
		std::vector<int32_t> reportUnit=unit->reports.log[0];// reports ?
		if( reportUnit.size()>0)
		{
			if(unit->name.has_name)
				out.print("%s aka. %s is fighting.\n",unit->name.first_name.c_str(),unit->name.nickname.c_str());
			else
				out.print("No name - display race & sex.\n");

			for (size_t j = 0; j < reportUnit.size(); j++)
			{
				int32_t refReport = reportUnit.at(j);
				combatLog.push_back(world->status.reports[relateReport(refReport,world->status.reports)]);

			}//end loop reportUnit
			printReport(out,combatLog);
			combatLog.clear();


		}//end if
	}//end for


    return CR_OK;
}

DFhackCExport command_result plugin_init ( color_ostream &out, vector <PluginCommand> &commands)
{
    commands.push_back(PluginCommand("combatLog","Display current combat log.",combatLog));
    return CR_OK;
}

void printReport(color_ostream &out,std::vector<df::report*> reports)
{
	size_t i;
	for ( i=0; i < reports.size()-1; i++)
	{
		if(reports[i+1]->flags.bits.continuation==1)
		{
			out.print("%s%s\n",reports[i]->text.c_str(),reports[i+1]->text.c_str());
			++i;
		}
		else
			out.print("%s\n",reports[i]->text.c_str());
	}
	if( i<reports.size())
		out.print("%s\n",reports[i]->text.c_str());
}

void printReportDebug(color_ostream &out,df::report *report)
{
    out.print(report->text.c_str());
	out.print("\n Type : %d - ", report->type);
	out.print("Flags.whole : %d - ",report->flags.whole);
	out.print("Flags.bits, announcement : %d - continuation : %d - unconscious : %d - ",report->flags.bits.announcement,report->flags.bits.continuation, report->flags.bits.unconscious);
	out.print("Color : %d -",report->color);
    out.print((report->bright?"Bright - ":"Not bright - "));
    out.print("Id : %d - ", report->id);
	out.print("Date : %d/%d .",report->year,report->time);
	out.print("\n");
}

int32_t relateReport(int32_t refReport,std::vector<df::report*> reports)
{
	for (size_t i=0; i < reports.size(); i++)
	{
		if( refReport == reports[i]->id )
			return i;
	}
	return -1;
}
