#include "sierrachart.h"
SCDLLName("Zone_to_File")
SCSFExport scsf_ZonesToFile(SCStudyInterfaceRef sc)
{
    SCInputRef Input_zone_study = sc.Input[0];

    
    if (sc.SetDefaults)
    {
        sc.GraphName = "Zones filled or unfilled data to file";
        sc.StudyDescription = "Checks for zones and stores into txt file.";
        
        sc.AutoLoop = 1;
        
        Input_zone_study.Name = "Input Zone Study";
        Input_zone_study.SetStudyID(1);
        
        sc.GraphRegion = 1;
        return;
    }
	
    int ZoneID = Input_zone_study.GetStudyID();
    int chartnumber = sc.ChartNumber;
    int ZoneArray = sc.GetNumLinesUntilFutureIntersection(chartnumber, ZoneID);
    int LineIDForBar = 0;
    int StartIndex = 0;
    float LineValue = 0.0f;
    int ExtensionLineChartColumnEndIndex = 0; 
    SCString Buffer;

        // Write the header row once
    Buffer += "LineID, Open_time, Value, Close_time, Above/Below\n";
    
    if (sc.Index == sc.ArraySize - 1 && ZoneArray > 0)
    {
        int FileHandle;
        
        // Open the file in write mode to overwrite its content
		

        // Loop through the zones and accumulate the data in Buffer
        for (int i = 0; i < ZoneArray; ++i)
        {
            sc.GetStudyLineUntilFutureIntersectionByIndex(chartnumber, ZoneID, i, LineIDForBar, StartIndex, LineValue, ExtensionLineChartColumnEndIndex);
            SCString startTimeString = sc.FormatDateTime(sc.BaseDateTimeIn[StartIndex]);
			float currentPrice = sc.BaseDataIn[SC_LAST][StartIndex];
			SCString zone_direction;

            if (ExtensionLineChartColumnEndIndex != 0)
            {
				SCString endTimeString = sc.FormatDateTime(sc.BaseDateTimeIn[ExtensionLineChartColumnEndIndex]);
				if (currentPrice < LineValue) {   
					zone_direction = "Above";
				}		
				else
					{
					zone_direction = "Below";
					}
                Buffer += SCString().Format("%d, %s, %.2f, %s, %s\n",
                    LineIDForBar,
                    startTimeString.GetChars(),
                    LineValue,
                    endTimeString.GetChars(),
					zone_direction.GetChars()
                );
            }
            else
            {
				if (currentPrice < LineValue) {   
					zone_direction = "Above";
				}		
				else
					{
					zone_direction = "Below";
					}
                Buffer += SCString().Format("%d, %s, %.2f, %s, %s\n",
                    LineIDForBar,
                    startTimeString.GetChars(),
                    LineValue,
					"Not Filled",
					zone_direction.GetChars()
                );
            }
        }
		SCString OutputFileName;
		OutputFileName.Format("%s-ZoneData.csv", sc.Symbol.GetChars());
		sc.OpenFile(OutputFileName, n_ACSIL::FILE_MODE_OPEN_TO_REWRITE_FROM_START, FileHandle);
		unsigned int BytesWritten = 0;
		
        // Write the entire buffer to the file
        sc.WriteFile(FileHandle, Buffer, Buffer.GetLength(), &BytesWritten);

        // Close the file after writing
        sc.CloseFile(FileHandle);
    }
}
