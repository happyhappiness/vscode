{
            case 2:
              this->ChipID.ProcessorName = "Cx6x86";
              break;
            case 4:
              this->ChipID.ProcessorName = "MediaGX GXm";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown Cx6x86 family";
              return false;
          }