# Python Execution Engine
This folder contains the Python code for the real-time execution engine that powers the **automated-liquidity-engine** project.
The engine reads market structure & option delta data, evaluates liquidity conditions, derives directional bias, and executes trades with a rule-based risk framework.
The system is designed purely for research and learning.

## Quickstart
Prerequisites
- Python 3.10+ 
- pip or Poetry
- Access to input data exports (per-minute bars, Sierra Chart liquidity, delta data)
- Optional: Discord webhook for alerts
  
## Contents
The engine performs the following tasks:

**Data Input**
- Load per-minute bar data
- Load liquidity zone data exported from Sierra Chart
- Load external delta data
- Clean and synchronize datasets

**Signal Logic**
- Liquidity zone analysis
- Liquidity gap detection
- Delta ROC calculation
- RSI-based extension logic
- Directional bias classification

**Execution Logic**
- Order placement
- Dynamic OCO targets
- Break-even transitions
- Conditional flattening
- Trailing stop adjustments

**Risk Controls**
- Max loss per day
- Daily profit target
- Allowed trading window
- Auto flatten after cutoff time

**Monitoring**
- Discord alerts
- Hourly chart exports

## High-Level Flow
1. Load new data
2. Recompute signals
3. Update liquidity & delta state
4. Check trading conditions / risk parameters
5. Submit / cancel / adjust orders
6. Enforce risk rules
7. Post message to discord about current state
8. Return to step 1

## Disclaimer

This code is for **research and education only**.  
It is not intended for live trading or production use.  
No guarantees are made regarding correctness or performance.
