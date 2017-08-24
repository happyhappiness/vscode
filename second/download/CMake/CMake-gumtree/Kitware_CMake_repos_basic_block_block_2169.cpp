{
        std::string fullDestPath = destination;
        fullDestPath += "/";
        fullDestPath += dir.GetFile(static_cast<unsigned long>(fileNum));
        if (!SystemTools::CopyADirectory(fullPath, fullDestPath, always)) {
          return false;
        }
      }