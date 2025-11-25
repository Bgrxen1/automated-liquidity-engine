#include "sierrachart.h"
SCDLLName("Liquidity_trend")
SCSFExport scsf_Liquidity_TrendV1(SCStudyInterfaceRef sc)
{
 SCInputRef Input_zone_study = sc.Input[0];
 SCInputRef Input_liq_flip = sc.Input[1];
 
 if (sc.SetDefaults)
    {
        sc.GraphName = "Liquidity Trend V1";
        sc.StudyDescription = "Checks for zones.";
        
        sc.AutoLoop = 1;
        
        Input_zone_study.Name = "Input Zone Study";
        Input_zone_study.SetStudyID(1);
		
		Input_liq_flip.Name = "Input minimum zones before liquidity flip (> or < comparison)";
        Input_liq_flip.SetInt(2);
        
        sc.GraphRegion = 2;
		SCSubgraphRef Cumulative_Unfilledzonesabove = sc.Subgraph[0];
        SCSubgraphRef Cumulative_Unfilledzonesbelow = sc.Subgraph[1];
        SCSubgraphRef Cumulative_Filledzonesabove = sc.Subgraph[2];
        SCSubgraphRef Cumulative_Filledzonesbelow = sc.Subgraph[3];
        SCSubgraphRef Unfilledzonesabove = sc.Subgraph[4];
        SCSubgraphRef Unfilledzonesbelow = sc.Subgraph[5];
        SCSubgraphRef Filledzonesabove = sc.Subgraph[6];
        SCSubgraphRef Filledzonesbelow = sc.Subgraph[7];
        SCSubgraphRef Cumulative_up_count = sc.Subgraph[8];
        SCSubgraphRef Cumulative_down_count = sc.Subgraph[9];
        SCSubgraphRef Liquidity_trend = sc.Subgraph[10];
		
        Unfilledzonesabove.Name = "Delta of Unfilled Zones Above";
        Unfilledzonesabove.DrawStyle = DRAWSTYLE_LINE;
        Unfilledzonesabove.PrimaryColor = RGB(0, 128, 255);

        Unfilledzonesbelow.Name = "Delta of Unfilled Zones Below";
        Unfilledzonesbelow.DrawStyle = DRAWSTYLE_LINE;
        Unfilledzonesbelow.PrimaryColor = RGB(0, 128, 255);

        Filledzonesabove.Name = "Delta of Filled Zones Above";
        Filledzonesabove.DrawStyle = DRAWSTYLE_LINE;
        Filledzonesabove.PrimaryColor = RGB(0, 128, 255);

        Filledzonesbelow.Name = "Delta of Filled Zones Below";
        Filledzonesbelow.DrawStyle = DRAWSTYLE_LINE;
        Filledzonesbelow.PrimaryColor = RGB(0, 128, 255);
		
		Cumulative_Unfilledzonesabove.Name = "Cumulative of Unfilled Zones Above";
        Cumulative_Unfilledzonesabove.DrawStyle = DRAWSTYLE_LINE;
        Cumulative_Unfilledzonesabove.PrimaryColor = RGB(0, 128, 255);

        Cumulative_Unfilledzonesbelow.Name = "Cumulative of Unfilled Zones Below";
        Cumulative_Unfilledzonesbelow.DrawStyle = DRAWSTYLE_LINE;
        Cumulative_Unfilledzonesbelow.PrimaryColor = RGB(0, 128, 255);

        Cumulative_Filledzonesabove.Name = "Cumulative of Filled Zones Above";
        Cumulative_Filledzonesabove.DrawStyle = DRAWSTYLE_LINE;
        Cumulative_Filledzonesabove.PrimaryColor = RGB(0, 128, 255);

        Cumulative_Filledzonesbelow.Name = "Cumulative of Filled Zones Below";
        Cumulative_Filledzonesbelow.DrawStyle = DRAWSTYLE_LINE;
        Cumulative_Filledzonesbelow.PrimaryColor = RGB(0, 128, 255);
		
		Cumulative_up_count.Name = "Cumulative Up Count";
        Cumulative_up_count.DrawStyle = DRAWSTYLE_HIDDEN;

        Cumulative_down_count.Name = "Cumulative Down Count";
        Cumulative_down_count.DrawStyle = DRAWSTYLE_HIDDEN;

        Liquidity_trend.Name = "Liquidity Trend";
        Liquidity_trend.DrawStyle = DRAWSTYLE_BACKGROUND;
        Liquidity_trend.PrimaryColor = RGB(0, 255, 0); // Green
        Liquidity_trend.SecondaryColorUsed = 1;
        Liquidity_trend.SecondaryColor = RGB(255, 0, 0); // Red
		Liquidity_trend.AutoColoring = AUTOCOLOR_POSNEG;


        return;
    }
	
	SCSubgraphRef Cumulative_Unfilledzonesabove = sc.Subgraph[0];
    SCSubgraphRef Cumulative_Unfilledzonesbelow = sc.Subgraph[1];
    SCSubgraphRef Cumulative_Filledzonesabove = sc.Subgraph[2];
    SCSubgraphRef Cumulative_Filledzonesbelow = sc.Subgraph[3];
	SCSubgraphRef Unfilledzonesabove = sc.Subgraph[4];
	SCSubgraphRef Unfilledzonesbelow = sc.Subgraph[5];
	SCSubgraphRef Filledzonesabove = sc.Subgraph[6];
	SCSubgraphRef Filledzonesbelow = sc.Subgraph[7];
        SCSubgraphRef Cumulative_up_count = sc.Subgraph[8];
        SCSubgraphRef Cumulative_down_count = sc.Subgraph[9];
        SCSubgraphRef Liquidity_trend = sc.Subgraph[10];
	
	int ZoneID = Input_zone_study.GetStudyID();
	int chartnumber = sc.ChartNumber;
	int barIndex = sc.UpdateStartIndex;	
	int ZoneArray = sc.GetNumLinesUntilFutureIntersection(chartnumber, ZoneID);
	int LineIDForBar = 0;
	int StartIndex = 0;
	float LineValue = 0.0f;
	int ExtensionLineChartColumnEndIndex = 0; 
	int Minimum_change = Input_liq_flip.GetInt();
	
    Unfilledzonesabove[sc.Index] = 0;
    Unfilledzonesbelow[sc.Index] = 0;
    Filledzonesabove[sc.Index] = 0;
    Filledzonesbelow[sc.Index] = 0;

for (int i = 0; i < ZoneArray; ++i) {

		sc.GetStudyLineUntilFutureIntersectionByIndex(chartnumber, ZoneID, i, LineIDForBar, StartIndex, LineValue, ExtensionLineChartColumnEndIndex);
		if (StartIndex == barIndex) 
        {
		float currentPrice = sc.BaseDataIn[SC_LAST][StartIndex];

		
		if (currentPrice < LineValue) {   
			Unfilledzonesabove[StartIndex] += 1;

		} else if (currentPrice > LineValue) {    
			Unfilledzonesbelow[StartIndex] += 1;
			
		}}
		if (ExtensionLineChartColumnEndIndex == barIndex) 
        {
		float currentPrice = sc.BaseDataIn[SC_LAST][StartIndex];
		
		if (ExtensionLineChartColumnEndIndex != 0) {
			if (currentPrice < LineValue) {  
				Unfilledzonesabove[ExtensionLineChartColumnEndIndex] -= 1;
				Filledzonesabove[ExtensionLineChartColumnEndIndex] += 1;

			} else if (currentPrice > LineValue) {    
				Unfilledzonesbelow[ExtensionLineChartColumnEndIndex] -= 1;
				Filledzonesbelow[ExtensionLineChartColumnEndIndex] += 1;

			}
		}}
}
    if (sc.Index == 0)
    {
        
        Cumulative_Filledzonesabove[sc.Index] = Filledzonesabove[sc.Index];
		Cumulative_Filledzonesbelow[sc.Index] = Filledzonesbelow[sc.Index];
		Cumulative_Unfilledzonesabove[sc.Index] = Unfilledzonesabove[sc.Index];
		Cumulative_Unfilledzonesbelow[sc.Index] = Unfilledzonesbelow [sc.Index];
		Cumulative_up_count[sc.Index] = 0;
		Cumulative_down_count[sc.Index] = 0;
		Liquidity_trend[sc.Index] = 1; 
    }
    else
    {
        
        Cumulative_Filledzonesabove[sc.Index] = Cumulative_Filledzonesabove[sc.Index - 1] + Filledzonesabove[sc.Index];
		Cumulative_Filledzonesbelow[sc.Index] = Cumulative_Filledzonesbelow[sc.Index - 1] + Filledzonesbelow[sc.Index];
		Cumulative_Unfilledzonesabove[sc.Index] = Cumulative_Unfilledzonesabove[sc.Index - 1] + Unfilledzonesabove[sc.Index];
		Cumulative_Unfilledzonesbelow[sc.Index] = Cumulative_Unfilledzonesbelow[sc.Index - 1] + Unfilledzonesbelow [sc.Index];
		
		Cumulative_up_count[sc.Index] = Cumulative_up_count[sc.Index - 1];
		Cumulative_down_count[sc.Index] = Cumulative_down_count[sc.Index - 1];
		Liquidity_trend[sc.Index] = Liquidity_trend[sc.Index - 1];

		
		if (Liquidity_trend[sc.Index] == 1)
		{
			if (Cumulative_Filledzonesbelow[sc.Index] > Cumulative_Filledzonesbelow[sc.Index - 1])
			{
				Cumulative_down_count[sc.Index] += Cumulative_Filledzonesbelow[sc.Index] - Cumulative_Filledzonesbelow[sc.Index - 1];
				
				
				if (Cumulative_down_count[sc.Index] > Minimum_change)
				{
					Liquidity_trend[sc.Index] = -1; // Flip to downtrend
					Cumulative_down_count[sc.Index] = 0; // Reset the counter
				}
			}

			
			if (Cumulative_Filledzonesabove[sc.Index] > Cumulative_Filledzonesabove[sc.Index - 1] && Cumulative_down_count[sc.Index] != 0)
			{
				Cumulative_down_count[sc.Index] = 0;
			}
		}
		
		else if (Liquidity_trend[sc.Index] == -1)
		{
			if (Cumulative_Filledzonesabove[sc.Index] > Cumulative_Filledzonesabove[sc.Index - 1])
			{
				Cumulative_up_count[sc.Index] += Cumulative_Filledzonesabove[sc.Index] - Cumulative_Filledzonesabove[sc.Index - 1];
				
				
				if (Cumulative_up_count[sc.Index] > Minimum_change)
				{
					Liquidity_trend[sc.Index] = 1; // Flip to uptrend
					Cumulative_up_count[sc.Index] = 0; // Reset the counter
				}
			}

			
			if (Cumulative_Filledzonesbelow[sc.Index] > Cumulative_Filledzonesbelow[sc.Index - 1] && Cumulative_up_count[sc.Index] != 0)
			{
				Cumulative_up_count[sc.Index] = 0;
			}
    }
    }
}
