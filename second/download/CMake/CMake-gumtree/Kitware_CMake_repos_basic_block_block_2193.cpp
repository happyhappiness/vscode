(strcmp(dir.GetFile(static_cast<unsigned long>(fileNum)), ".") &&
        strcmp(dir.GetFile(static_cast<unsigned long>(fileNum)), "..")) {
      std::string fullPath = source;
      fullPath += "/";
      fullPath += dir.GetFile(static_cast<unsigned long>(fileNum));
      if (SystemTools::FileIsDirectory(fullPath) &&
          !SystemTools::FileIsSymlink(fullPath)) {
        if (!SystemTools::RemoveADirectory(fullPath)) {
          return false;
        }
      } else {
        if (!SystemTools::RemoveFile(fullPath)) {
          return false;
        }
      }
    }