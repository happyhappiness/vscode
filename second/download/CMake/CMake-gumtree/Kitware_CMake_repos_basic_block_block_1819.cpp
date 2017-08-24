{
            case 0:
              this->ChipID.ProcessorName = "SSA5 (PR75, PR90 =  PR100)";
              break;
            case 1:
              this->ChipID.ProcessorName = "5k86 (PR120 =  PR133)";
              break;
            case 2:
              this->ChipID.ProcessorName = "5k86 (PR166)";
              break;
            case 3:
              this->ChipID.ProcessorName = "5k86 (PR200)";
              break;
            case 6:
              this->ChipID.ProcessorName = "K6 (0.30 micron)";
              break;
            case 7:
              this->ChipID.ProcessorName = "K6 (0.25 micron)";
              break;
            case 8:
              this->ChipID.ProcessorName = "K6-2";
              break;
            case 9:
              this->ChipID.ProcessorName = "K6-III";
              break;
            case 0xd:
              this->ChipID.ProcessorName = "K6-2+ or K6-III+ (0.18 micron)";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown 80586 family";
              return false;
          }