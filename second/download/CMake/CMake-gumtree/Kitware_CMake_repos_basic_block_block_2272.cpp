{
  std::string casePath;
  std::vector<std::string> path_components;
  SystemTools::SplitPath(pathIn, path_components);
  if (path_components[0].empty()) // First component always exists.
  {
    // Relative paths cannot be converted.
    casePath = pathIn;
    return casePath;
  }

  // Start with root component.
  std::vector<std::string>::size_type idx = 0;
  casePath = path_components[idx++];
  // make sure drive letter is always upper case
  if (casePath.size() > 1 && casePath[1] == ':') {
    casePath[0] = toupper(casePath[0]);
  }
  const char* sep = "";

  // If network path, fill casePath with server/share so FindFirstFile
  // will work after that.  Maybe someday call other APIs to get
  // actual case of servers and shares.
  if (path_components.size() > 2 && path_components[0] == "//") {
    casePath += path_components[idx++];
    casePath += "/";
    casePath += path_components[idx++];
    sep = "/";
  }

  // Convert case of all components that exist.
  bool converting = true;
  for (; idx < path_components.size(); idx++) {
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
  return casePath;
}