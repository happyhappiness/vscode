{
    casePath += sep;
    sep = "/";

    if (converting) {
      // If path component contains wildcards, we skip matching
      // because these filenames are not allowed on windows,
      // and we do not want to match a different file.
      if (path_components[idx].find('*') != std::string::npos ||
          path_components[idx].find('?') != std::string::npos) {
        converting = false;
      } else {
        std::string test_str = casePath;
        test_str += path_components[idx];
        WIN32_FIND_DATAW findData;
        HANDLE hFind =
          ::FindFirstFileW(Encoding::ToWide(test_str).c_str(), &findData);
        if (INVALID_HANDLE_VALUE != hFind) {
          path_components[idx] = Encoding::ToNarrow(findData.cFileName);
          ::FindClose(hFind);
        } else {
          converting = false;
        }
      }
    }

    casePath += path_components[idx];
  }