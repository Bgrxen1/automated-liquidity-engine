# Sierra Chart Studies (ACSIL)

This folder contains the C++ / ACSIL studies I use in Sierra Chart to extract and structure market data for the **automated-liquidity-engine** project.

## Goal
The goal of these studies is to:
- track liquidity (filled / unfilled),
- export clean zone-level data to CSV,
- and make that data easy to consume from Python.

## Contents
- **Zone_export.cpp**
  This study opens the container in which the extension lines are collected, iterates through the lines and outputs every line in a standard format into a csv file.
- **Liquidity_trend.cpp**
  This study calculates the Current accepted Liquidity inside Sierrachart instead of the python engine. This saves a couple miliseconds within the whole engine when used. as a study and outputs a 1 or -1 based on if the last accepted liquidity was   created above or below price. 
- **Liquidity_trendV2.cpp**
  This study calculates the current accepted liquidity based on the current prices and groups liquidity from the current price period and outside period, looking for acceptance of liquidity of the outside price period.
  
## How this integrates with the project

These studies:
1. run on a live Sierra Chart instance,
2. extract real-time structure and zone information,
3. write that data to CSV,
4. which is then consumed by the Python engine in `/liquidity_engine/`.
This allows the engine to evaluate liquidity structure, detect changes, and manage trades in real time.

## Disclaimer
These Sierra Chart studies are experimental and for **research purposes only**.  
They are not audited, and there is no guarantee of correctness or suitability for live trading.  
Use them at your own risk.
