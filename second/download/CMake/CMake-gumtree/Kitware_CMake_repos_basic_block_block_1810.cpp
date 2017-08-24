{
            case 6:
              this->ChipID.ProcessorName = "VIA Cyrix III - Samuel";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown IDT\\Centaur family";
              return false;
          }