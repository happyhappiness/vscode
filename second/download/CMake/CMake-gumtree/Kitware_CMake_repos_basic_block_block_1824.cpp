{
    case Intel:
      // Check the family / model / revision to determine the CPU ID.
      switch (this->ChipID.Family) {
        case 3:
          this->ChipID.ProcessorName = "Newer i80386 family";
          break;
        case 4:
          switch (this->ChipID.Model) {
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
          break;
        case 5:
          switch (this->ChipID.Model) {
            case 0:
              this->ChipID.ProcessorName = "P5 A-Step";
              break;
            case 1:
              this->ChipID.ProcessorName = "P5";
              break;
            case 2:
              this->ChipID.ProcessorName = "P54C";
              break;
            case 3:
              this->ChipID.ProcessorName = "P24T OverDrive";
              break;
            case 4:
              this->ChipID.ProcessorName = "P55C";
              break;
            case 7:
              this->ChipID.ProcessorName = "P54C";
              break;
            case 8:
              this->ChipID.ProcessorName = "P55C (0.25micron)";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown Pentium family";
              return false;
          }
          break;
        case 6:
          switch (this->ChipID.Model) {
            case 0:
              this->ChipID.ProcessorName = "P6 A-Step";
              break;
            case 1:
              this->ChipID.ProcessorName = "P6";
              break;
            case 3:
              this->ChipID.ProcessorName = "Pentium II (0.28 micron)";
              break;
            case 5:
              this->ChipID.ProcessorName = "Pentium II (0.25 micron)";
              break;
            case 6:
              this->ChipID.ProcessorName = "Pentium II With On-Die L2 Cache";
              break;
            case 7:
              this->ChipID.ProcessorName = "Pentium III (0.25 micron)";
              break;
            case 8:
              this->ChipID.ProcessorName =
                "Pentium III (0.18 micron) With 256 KB On-Die L2 Cache ";
              break;
            case 0xa:
              this->ChipID.ProcessorName =
                "Pentium III (0.18 micron) With 1 Or 2 MB On-Die L2 Cache ";
              break;
            case 0xb:
              this->ChipID.ProcessorName = "Pentium III (0.13 micron) With "
                                           "256 Or 512 KB On-Die L2 Cache ";
              break;
            case 23:
              this->ChipID.ProcessorName =
                "Intel(R) Core(TM)2 Duo CPU     T9500  @ 2.60GHz";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown P6 family";
              return false;
          }
          break;
        case 7:
          this->ChipID.ProcessorName = "Intel Merced (IA-64)";
          break;
        case 0xf:
          // Check the extended family bits...
          switch (this->ChipID.ExtendedFamily) {
            case 0:
              switch (this->ChipID.Model) {
                case 0:
                  this->ChipID.ProcessorName = "Pentium IV (0.18 micron)";
                  break;
                case 1:
                  this->ChipID.ProcessorName = "Pentium IV (0.18 micron)";
                  break;
                case 2:
                  this->ChipID.ProcessorName = "Pentium IV (0.13 micron)";
                  break;
                default:
                  this->ChipID.ProcessorName = "Unknown Pentium 4 family";
                  return false;
              }
              break;
            case 1:
              this->ChipID.ProcessorName = "Intel McKinley (IA-64)";
              break;
            default:
              this->ChipID.ProcessorName = "Pentium";
          }
          break;
        default:
          this->ChipID.ProcessorName = "Unknown Intel family";
          return false;
      }
      break;

    case AMD:
      // Check the family / model / revision to determine the CPU ID.
      switch (this->ChipID.Family) {
        case 4:
          switch (this->ChipID.Model) {
            case 3:
              this->ChipID.ProcessorName = "80486DX2";
              break;
            case 7:
              this->ChipID.ProcessorName = "80486DX2 WriteBack";
              break;
            case 8:
              this->ChipID.ProcessorName = "80486DX4";
              break;
            case 9:
              this->ChipID.ProcessorName = "80486DX4 WriteBack";
              break;
            case 0xe:
              this->ChipID.ProcessorName = "5x86";
              break;
            case 0xf:
              this->ChipID.ProcessorName = "5x86WB";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown 80486 family";
              return false;
          }
          break;
        case 5:
          switch (this->ChipID.Model) {
            case 0:
              this->ChipID.ProcessorName = "SSA5 (PR75, PR90 =  PR100)";
              break;
            case 1:
              this->ChipID.ProcessorName = "5k86 (PR120 =  PR133)";
              break;
            case 2:
              this->ChipID.ProcessorName = "5k86 (PR166)";
              break;
            case 3:
              this->ChipID.ProcessorName = "5k86 (PR200)";
              break;
            case 6:
              this->ChipID.ProcessorName = "K6 (0.30 micron)";
              break;
            case 7:
              this->ChipID.ProcessorName = "K6 (0.25 micron)";
              break;
            case 8:
              this->ChipID.ProcessorName = "K6-2";
              break;
            case 9:
              this->ChipID.ProcessorName = "K6-III";
              break;
            case 0xd:
              this->ChipID.ProcessorName = "K6-2+ or K6-III+ (0.18 micron)";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown 80586 family";
              return false;
          }
          break;
        case 6:
          switch (this->ChipID.Model) {
            case 1:
              this->ChipID.ProcessorName = "Athlon- (0.25 micron)";
              break;
            case 2:
              this->ChipID.ProcessorName = "Athlon- (0.18 micron)";
              break;
            case 3:
              this->ChipID.ProcessorName = "Duron- (SF core)";
              break;
            case 4:
              this->ChipID.ProcessorName = "Athlon- (Thunderbird core)";
              break;
            case 6:
              this->ChipID.ProcessorName = "Athlon- (Palomino core)";
              break;
            case 7:
              this->ChipID.ProcessorName = "Duron- (Morgan core)";
              break;
            case 8:
              if (this->Features.ExtendedFeatures.SupportsMP)
                this->ChipID.ProcessorName = "Athlon - MP (Thoroughbred core)";
              else
                this->ChipID.ProcessorName = "Athlon - XP (Thoroughbred core)";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown K7 family";
              return false;
          }
          break;
        default:
          this->ChipID.ProcessorName = "Unknown AMD family";
          return false;
      }
      break;

    case Transmeta:
      switch (this->ChipID.Family) {
        case 5:
          switch (this->ChipID.Model) {
            case 4:
              this->ChipID.ProcessorName = "Crusoe TM3x00 and TM5x00";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown Crusoe family";
              return false;
          }
          break;
        default:
          this->ChipID.ProcessorName = "Unknown Transmeta family";
          return false;
      }
      break;

    case Rise:
      switch (this->ChipID.Family) {
        case 5:
          switch (this->ChipID.Model) {
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
          break;
        default:
          this->ChipID.ProcessorName = "Unknown Rise family";
          return false;
      }
      break;

    case UMC:
      switch (this->ChipID.Family) {
        case 4:
          switch (this->ChipID.Model) {
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
          break;
        default:
          this->ChipID.ProcessorName = "Unknown UMC family";
          return false;
      }
      break;

    case IDT:
      switch (this->ChipID.Family) {
        case 5:
          switch (this->ChipID.Model) {
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
          break;
        case 6:
          switch (this->ChipID.Model) {
            case 6:
              this->ChipID.ProcessorName = "VIA Cyrix III - Samuel";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown IDT\\Centaur family";
              return false;
          }
          break;
        default:
          this->ChipID.ProcessorName = "Unknown IDT\\Centaur family";
          return false;
      }
      break;

    case Cyrix:
      switch (this->ChipID.Family) {
        case 4:
          switch (this->ChipID.Model) {
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
          break;
        case 5:
          switch (this->ChipID.Model) {
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
          break;
        case 6:
          switch (this->ChipID.Model) {
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
          break;
        default:
          this->ChipID.ProcessorName = "Unknown Cyrix family";
          return false;
      }
      break;

    case NexGen:
      switch (this->ChipID.Family) {
        case 5:
          switch (this->ChipID.Model) {
            case 0:
              this->ChipID.ProcessorName = "Nx586 or Nx586FPU";
              break;
            default:
              this->ChipID.ProcessorName = "Unknown NexGen family";
              return false;
          }
          break;
        default:
          this->ChipID.ProcessorName = "Unknown NexGen family";
          return false;
      }
      break;

    case NSC:
      this->ChipID.ProcessorName = "Cx486SLC \\ DLC \\ Cx486S A-Step";
      break;

    case Sun:
    case IBM:
    case Motorola:
    case HP:
    case UnknownManufacturer:
    default:
      this->ChipID.ProcessorName =
        "Unknown family"; // We cannot identify the processor.
      return false;
  }