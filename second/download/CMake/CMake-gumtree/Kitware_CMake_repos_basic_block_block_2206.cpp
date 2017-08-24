{
      tryPath = *p;
      tryPath += name;
      tryPath += *ext;
      if (SystemTools::FileExists(tryPath, true)) {
        return SystemTools::CollapseFullPath(tryPath);
      }
    }