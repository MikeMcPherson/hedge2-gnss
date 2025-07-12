# Gnss::Gnss

Read NMEA sentences from the GNSS receiver, parse them, 
process the data, update telemetry, update logs, 
and store the data for other Components

## Requirements
Add requirements in the chart below
| Name | Description | Validation |
|---|---|---|
| Gnss-01 | Shall read NMEA sentences from GNSS receiver | Unit test |
| Gnss-02 | Shall parse NMEA sentences | Unit test |
| Gnss-03 | Shall extract fix quality, position, altitude, speed, and heading from NMEA sentences | Unit test |
| Gnss-04 | Shall emit telemetry and log changes in that data | Unit test |
| Gnss-05 | Shall make that data available for use by other Components | Unit test |

## Usage Examples

### Diagrams

### Typical Usage

## Class Diagram

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
| GNSS disabled | Fw::On::OFF |
| GNSS enabled | Fw::On::ON |

## Sequence Diagrams

## Parameters
| Name | Description |
|---|---|

## Commands
| Name | Description |
|---|---|
| gnssEnable | Enable or disable GNSS, argument Fw:On |

## Events
| Name | Description |
|---|---|
| gnssState | GNSS enabled or disabled |
| fixValidity | Valid fix acquired |
| gpsQuality | GPS quality field from the NMEA GGA sentence |

## Telemetry
| Name | Description |
|---|---|
| numSentences | Number of NMEA sentences processed since GNSS enabled |
| latitude | current GGA latitude, in degrees |
| longitude | current GGA longitude, in degrees |
| altitude | current GGA altitude, in meters |
| speed | current RMC speed, in knots |
| heading | current RMC track angle, in degrees from True North |

## Unit Tests
Add unit test descriptions in the chart below
| Name | Description | Output | Coverage |
|---|---|---|---|
|---|---|---|---|

## Change Log
| Date | Description | Author |
|---|---|---|
| 12 July 2025 | Initial Draft | MRM |