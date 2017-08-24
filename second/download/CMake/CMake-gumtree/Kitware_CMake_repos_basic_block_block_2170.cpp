{
      std::string fullPath = source;
      fullPath += "/";
      fullPath += dir.GetFile(static_cast<unsigned long>(fileNum));
      if (SystemTools::FileIsDirectory(fullPath)) {
        std::string fullDestPath = destination;
        fullDestPath += "/";
        fullDestPath += dir.GetFile(static_cast<unsigned long>(fileNum));
        if (!SystemTools::CopyADirectory(fullPath, fullDestPath, always)) {
          return false;
        }
      } else {
        if (!SystemTools::CopyAFile(fullPath, destination, always)) {
          return false;
        }
      }
    }