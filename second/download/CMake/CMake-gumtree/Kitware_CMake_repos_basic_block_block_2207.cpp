(std::vector<std::string>::iterator ext = extensions.begin();
         ext != extensions.end(); ++ext) {
      tryPath = *p;
      tryPath += name;
      tryPath += *ext;
      if (SystemTools::FileExists(tryPath, true)) {
        return SystemTools::CollapseFullPath(tryPath);
      }
    }