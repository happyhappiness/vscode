{
            case 1:
              this->ChipID.ProcessorName = "U5D";
              break;
            case 2:
              this->ChipID.ProcessorName = "U5S";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown UMC family";
              return false;
          }