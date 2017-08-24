{
            case 4:
              this->ChipID.ProcessorName = "Crusoe TM3x00 and TM5x00";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown Crusoe family";
              return false;
          }