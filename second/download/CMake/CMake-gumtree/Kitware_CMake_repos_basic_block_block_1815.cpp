{
            case 0:
              this->ChipID.ProcessorName = "mP6 (0.25 micron)";
              break;
            case 2:
              this->ChipID.ProcessorName = "mP6 (0.18 micron)";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown Rise family";
              return false;
          }