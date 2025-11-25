#include "sierrachart.h"
SCDLLName("Liquidity Trend V2")
SCSFExport scsf_Liquidity_TrendV2(SCStudyInterfaceRef sc)
{
    SCInputRef Tickspread = sc.Input[0];
	SCInputRef Input_zone_study = sc.Input[1];
	
    if (sc.SetDefaults)
    {
        sc.GraphName = "Liquidity Trend V2";
        sc.StudyDescription = "Caclulates a range of which price trades inside, the longer the line the longer the consolidation period inside a tight period";
        
        sc.AutoLoop = 1;
        
        Tickspread.Name = "Tick spread of closes";
        Tickspread.SetInt(20);
		
		Input_zone_study.Name = "Input Zone Study";
        Input_zone_study.SetStudyID(1);
        
		sc.GraphRegion = 1;

		SCSubgraphRef Highline = sc.Subgraph[0];
		SCSubgraphRef Lowline = sc.Subgraph[1];
		SCSubgraphRef Period = sc.Subgraph[2];
		SCSubgraphRef Unfilled_zones_above = sc.Subgraph[3];
		SCSubgraphRef Filled_zones_above = sc.Subgraph[4];
		SCSubgraphRef Liquidity_trend = sc.Subgraph[5];

		
		Highline.Name = "Highline of chop";
		Highline.DrawStyle = DRAWSTYLE_HIDDEN;
		Highline.PrimaryColor = RGB(0,255, 0);
		
		Lowline.Name = "Lowline of chop";
		Lowline.DrawStyle = DRAWSTYLE_HIDDEN;
		Lowline.PrimaryColor = RGB(0,255, 0);
		
		Period.Name = "Period of creation";
		Period.DrawStyle = DRAWSTYLE_HIDDEN;
		
		Liquidity_trend.Name = "Liquidity Trend V2";
        Liquidity_trend.DrawStyle = DRAWSTYLE_BACKGROUND;
        Liquidity_trend.PrimaryColor = RGB(0, 255, 0); // Green
        Liquidity_trend.SecondaryColorUsed = 1;
        Liquidity_trend.SecondaryColor = RGB(255, 0, 0); // Red
		Liquidity_trend.AutoColoring = AUTOCOLOR_POSNEG;

        return;
    }

    SCSubgraphRef Highline = sc.Subgraph[0];
	SCSubgraphRef Lowline = sc.Subgraph[1];
	SCSubgraphRef Period = sc.Subgraph[2];
	SCSubgraphRef Unfilled_zones_above = sc.Subgraph[3];
	SCSubgraphRef Filled_zones_above = sc.Subgraph[4];
	SCSubgraphRef Liquidity_trend = sc.Subgraph[5];

	
	int range = Tickspread.GetInt();
	float Tickrange = range * sc.TickSize;
	int ZoneID = Input_zone_study.GetStudyID();
	int chartnumber = sc.ChartNumber;
	int ZoneArray = sc.GetNumLinesUntilFutureIntersection(chartnumber, ZoneID);
	int LineIDForBar = 0;
	int StartIndex = 0;
	float LineValue = 0.0f;
	int ExtensionLineChartColumnEndIndex = 0;
	int Last_filled_zone_index = 0;
	int Last_filled_zone_id = 0;
	int barIndex = sc.UpdateStartIndex;
	Liquidity_trend[sc.Index] = 0;
	
	if (sc.Index == 0)
	{
		Highline[sc.Index] = sc.High[sc.Index] + Tickrange;
		Lowline[sc.Index] = sc.Low[sc.Index] - Tickrange;
		Period[sc.Index] = 0;
		
	}
	
	if (Lowline[sc.Index -1] > sc.Low[sc.Index -1])
	{
		Lowline[sc.Index] = Lowline[sc.Index -1] - Tickrange;
		Highline[sc.Index] = Highline[sc.Index -1] - Tickrange;
		Period[sc.Index] = Period[sc.Index - 1] + 1;
	}
	else if (Highline[sc.Index - 1] < sc.High[sc.Index -1])
	{
		Lowline[sc.Index] = Lowline[sc.Index -1] + Tickrange;
		Highline[sc.Index] = Highline[sc.Index -1] + Tickrange;
		Period[sc.Index] = Period[sc.Index - 1] + 1;
	}
	else
	{
		Lowline[sc.Index] = Lowline[sc.Index -1];
		Highline[sc.Index] = Highline[sc.Index -1];	
		Period[sc.Index] = Period[sc.Index - 1];
	}

	for (int i = 0; i < ZoneArray; ++i) {

		sc.GetStudyLineUntilFutureIntersectionByIndex(chartnumber, ZoneID, i, LineIDForBar, StartIndex, LineValue, ExtensionLineChartColumnEndIndex);
		if (ExtensionLineChartColumnEndIndex == barIndex)
        {
		float currentPrice = sc.BaseDataIn[SC_LAST][StartIndex];
		
		if (ExtensionLineChartColumnEndIndex != 0) {
			if (Period[StartIndex] != Period[barIndex])
			{
				if (currentPrice < LineValue) {  
					Liquidity_trend[barIndex] = 1;

			}	else if (currentPrice > LineValue) {    
					Liquidity_trend[barIndex] = -1;
			}
			}
		}
	}
}
	if (Liquidity_trend[barIndex] == 0)
	{
		Liquidity_trend[barIndex] = Liquidity_trend[barIndex - 1];
	}
}
