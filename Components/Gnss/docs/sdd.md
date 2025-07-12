# Gnss::Gnss

GNSS read, parse, process, and log

## Usage Examples
Add usage examples here

### Diagrams
Add diagrams here

### Typical Usage
And the typical usage of the component here

## Class Diagram
Add a class diagram here

## Port Descriptions
| Name | Description |
|---|---|
| gnssRecv | Receive GNSS sentences |
| gnssSend | Send commands to the GNSS receiver |
| deallocate | Return buffer to BufferManager |

## Component States
Add component states in the chart below
| Name | Description |
|---|---|
| Fw::On::OFF | GNSS disabled |
| Fw::On::ON | GNSS enabled |

## Sequence Diagrams
Add sequence diagrams here

## Parameters
| Name | Description |
|---|---|

## Commands
| Name | Description |
|---|---|
| gnssEnable | Enable or disable GNSS |

## Events
| Name | Description |
|---|---|
| gnssState | GNSS enabled or disabled |
| fixValidity | Valid fix |
| gpsQuality | GPS quality field from the NMEA GGA sentence |

## Telemetry
| Name | Description |
|---|---|
| numSentences |---|
| latitude |---|
| longitude |---|
| altitude |---|
| speed |---|
| heading |---|

## Unit Tests
Add unit test descriptions in the chart below
| Name | Description | Output | Coverage |
|---|---|---|---|
|---|---|---|---|

## Requirements
Add requirements in the chart below
| Name | Description | Validation |
|---|---|---|
|---|---|---|

## Change Log
| Date | Description | Author |
|---|---|---|
| 12 July 2025 | Initial Draft | MRM |