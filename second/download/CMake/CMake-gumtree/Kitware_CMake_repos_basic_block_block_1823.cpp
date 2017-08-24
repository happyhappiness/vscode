{
            case 0:
              this->ChipID.ProcessorName = "i80486DX-25/33";
              break;
            case 1:
              this->ChipID.ProcessorName = "i80486DX-50";
              break;
            case 2:
              this->ChipID.ProcessorName = "i80486SX";
              break;
            case 3:
              this->ChipID.ProcessorName = "i80486DX2";
              break;
            case 4:
              this->ChipID.ProcessorName = "i80486SL";
              break;
            case 5:
              this->ChipID.ProcessorName = "i80486SX2";
              break;
            case 7:
              this->ChipID.ProcessorName = "i80486DX2 WriteBack";
              break;
            case 8:
              this->ChipID.ProcessorName = "i80486DX4";
              break;
            case 9:
              this->ChipID.ProcessorName = "i80486DX4 WriteBack";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown 80486 family";
              return false;
          }