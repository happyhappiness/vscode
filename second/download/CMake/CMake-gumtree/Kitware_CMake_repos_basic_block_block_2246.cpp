(SystemTools::FileIsFullPath(path_b) &&
        path_b.find("..") == std::string::npos) {
      // Before inserting make sure path ends with '/'
      if (!path_a.empty() && *path_a.rbegin() != '/') {
        path_a += '/';
      }
      if (!path_b.empty() && *path_b.rbegin() != '/') {
        path_b += '/';
      }
      if (!(path_a == path_b)) {
        SystemTools::TranslationMap->insert(
          SystemToolsTranslationMap::value_type(path_a, path_b));
      }
    }