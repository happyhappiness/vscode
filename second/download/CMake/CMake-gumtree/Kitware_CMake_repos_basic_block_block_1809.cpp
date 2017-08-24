{
            case 4:
              this->ChipID.ProcessorName = "MediaGX GX =  GXm";
              break;
            case 9:
              this->ChipID.ProcessorName = "5x86";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown Cx5x86 family";
              return false;
          }