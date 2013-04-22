#include "Core.h"
#include "Console.h"
#include "PluginManager.h"

#include "DataDefs.h"
#include "df/world.h"
#include "df/report.h"
#include "df/announcement_type.h"
#include "df/unit.h"
#include "df/viewscreen_reportlistst.h"

using std::string;
using std::vector;

using namespace DFHack;
using namespace df::enums;

using df::global::world;

DFHACK_PLUGIN("combatLog");
void printReport(color_ostream &out,df::report *report);


command_result combatLog (color_ostream &out, vector <string> & parameters)
{
	out.print("Report number :  %d.\n", world->status.reports.size());
	out.print("Annoucement number :  %d.\n", world->status.announcements.size());


	for (size_t i = 0; i < world->status.reports.size(); i++)
	{
		df::report *report=world->status.reports[i];
		if(report->type != 103)
		{
			printReport(out,report);
		}
	}//end for

	int unitReportCounter=0;

	out.print("Active units : %d",world->units.active.size());
	for (size_t i = 0; i < world->units.active.size(); i++)
	{
		df::unit *unit=world->units.active[i];
		int log1=unit->reports.log[0].size();
		int log2=unit->reports.log[1].size();
		int log3=unit->reports.log[2].size();
		if(log1>0 || log2>0 || log3>0)
		{
			out.print("Unit id %d has those log size : %d %d %d.\n",unit->id,log1, log2, log3);
		}
	}//end for


    return CR_OK;
}

DFhackCExport command_result plugin_init ( color_ostream &out, vector <PluginCommand> &commands)
{
    commands.push_back(PluginCommand("combatLog","Display current combat log.",combatLog));
    return CR_OK;
}

void printReport(color_ostream &out,df::report *report){
	out.print("Type : %d - ", report->type);
    out.print(report->text.c_str());
	out.print("Color : %d -",report->color);
    out.print((report->bright?"Bright":"Not bright"));
    out.print("Duration : %d - ", report->duration);
	out.print("Date : %d - %d/%d .",report->id,report->year,report->time);
	out.print("\n");
}
