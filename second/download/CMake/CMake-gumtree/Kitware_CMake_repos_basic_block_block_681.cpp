(cmSystemTools::GetFilenameName(filePath) == "CMakeCache.txt" &&
          cmSystemTools::FileExists(filePath.c_str())) {
        buildFilePath = filePath;
      }