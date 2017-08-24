{
            case 0:
              this->ChipID.ProcessorName = "6x86MX";
              break;
            case 5:
              this->ChipID.ProcessorName = "Cyrix M2 Core";
              break;
            case 6:
              this->ChipID.ProcessorName = "WinChip C5A Core";
              break;
            case 7:
              this->ChipID.ProcessorName = "WinChip C5B\\C5C Core";
              break;
            case 8:
              this->ChipID.ProcessorName = "WinChip C5C-T Core";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown 6x86MX\\Cyrix III family";
              return false;
          }