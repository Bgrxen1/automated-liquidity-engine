# Automated-Liquidity-Engine
A Python-based live trading engine that processes market data from Sierra Chart, combines it with real-time option delta signals from AWS, and generates automated execution decisions.
The system also includes visualization, Discord notifications, and modular Sierra Chart studies written in ASCIL (Derrivative of C++).

## System Architecture
The system combines multiple real-time data sources, processing them through the Python Engine, and routing trading decisions to Sierra Chart via a bridge while outputting analytics to Discord as shown in the picture below.
![System Architecture](data/pictures/System_architecture.png)

### How It Works (High-Level)
1. **Market data** arrives from Sierra Chart.  
2. **Option delta** values are downloaded from AWS.  
3. The **Python Engine** processes both streams by:
   - building liquidity zones  
   - detecting price reactions  
   - calculating directional bias  
   - determining valid trade entries/exits  
4. The **Execution Layer** sends trade actions to Sierra Chart.  
5. **Discord Output** provides live signals and summary messages.

## Example outputs
### This picture shows the minutely update from the engine into a discord webhook showing the  flipping of bias:
<img src="data/pictures/discord_output_example.png" width="450">

### This picture shows the output that is generated everytime the engine does a full run so I could track how fast it was calculating: (note 5 second sleep timer)
<img src="data/pictures/python_output_example.png" width="450">

### This picture shows the chart that is posted to discord every hour
<img src="data/pictures/image.png" width="450">

### This picture shows a chart of a full day of signals
<img src="data/pictures/full_day_example.png" width="450">

## Repository Structure

automated-liquidity-engine/
|
├── README.md                 # Main documentation
├── config.example.json       # Example config for the engine
├── LICENSE                   # MIT license
|
├── data/
│   └── data_examples/        # Sample datasets for testing the engine
│       ├── ES_data_example.csv
│       └── zone_data_example.csv
|
├── images/                   # Architecture and output screenshots
│   ├── System_architecture.png
│   ├── python_output_example.png
│   └── execution_example.png
|
├── liquidity_engine/
│   ├── README.md             # Documentation for the engine
│   ├── trading_engine.ipynb  # Main engine notebook
│   └── sierra_chart/         # Sierra Chart studies (C++)
│       └── README.md
|
└── .gitignore


## Documentation
- [Engine Documentation](liquidity_engine/README.md)
- [Sierra Chart Studies](sierrachart/README.md)

## License
This project is licensed under the MIT License.  
See the LICENSE file for details.
