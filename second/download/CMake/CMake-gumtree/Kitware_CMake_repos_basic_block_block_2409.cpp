(osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0) {
        if (osvi.wProductType == VER_NT_WORKSTATION) {
          res += "Microsoft Windows 10";
        } else {
          res += "Microsoft Windows Server 2016 family";
        }
      }