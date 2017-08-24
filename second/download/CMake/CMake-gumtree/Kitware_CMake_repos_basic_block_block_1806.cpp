(this->ChipID.Model) {
            case 0:
              this->ChipID.ProcessorName = "Nx586 or Nx586FPU";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown NexGen family";
              return false;
          }