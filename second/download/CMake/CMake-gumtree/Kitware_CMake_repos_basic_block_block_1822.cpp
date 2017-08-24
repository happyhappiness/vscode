{
            case 0:
              this->ChipID.ProcessorName = "P5 A-Step";
              break;
            case 1:
              this->ChipID.ProcessorName = "P5";
              break;
            case 2:
              this->ChipID.ProcessorName = "P54C";
              break;
            case 3:
              this->ChipID.ProcessorName = "P24T OverDrive";
              break;
            case 4:
              this->ChipID.ProcessorName = "P55C";
              break;
            case 7:
              this->ChipID.ProcessorName = "P54C";
              break;
            case 8:
              this->ChipID.ProcessorName = "P55C (0.25micron)";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown Pentium family";
              return false;
          }