# Gnss::Gnss

Read NMEA sentences from the GNSS receiver, parse them, 
process the data, update telemetry, update logs, 
and store the data for other Components

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
| Fw::On::OFF | GNSS disabled |
| Fw::On::ON | GNSS enabled |

## Sequence Diagrams

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
| fixValidity | Valid fix acquired |
| gpsQuality | GPS quality field from the NMEA GGA sentence |

## Telemetry
| Name | Description |
|---|---|
| numSentences | Number of NMEA sentences processed since GNSS enabled |
| latitude | GGA latitude, in degrees |
| longitude | GGA longitude, in degrees |
| altitude | GGA altitude, in meters |
| speed | RMC speed, in knots |
| heading | RMC track angle, in degrees from True North |

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