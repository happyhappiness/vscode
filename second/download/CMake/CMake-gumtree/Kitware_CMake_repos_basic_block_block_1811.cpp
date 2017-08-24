{
            case 4:
              this->ChipID.ProcessorName = "C6";
              break;
            case 8:
              this->ChipID.ProcessorName = "C2";
              break;
            case 9:
              this->ChipID.ProcessorName = "C3";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown IDT\\Centaur family";
              return false;
          }