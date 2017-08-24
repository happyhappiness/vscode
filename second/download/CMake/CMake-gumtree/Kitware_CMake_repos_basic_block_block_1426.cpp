(cp->RealWorkingDirectoryLength > 0) {
      cp->RealWorkingDirectory =
        malloc(cp->RealWorkingDirectoryLength * sizeof(wchar_t));
      if (!cp->RealWorkingDirectory) {
        return 0;
      }
    }