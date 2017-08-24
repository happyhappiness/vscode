{
  // Do not translate paths that are too short to have meaningful
  // translations.
  if (path.size() < 2) {
    return;
  }

  // Always add a trailing slash before translation.  It does not
  // matter if this adds an extra slash, but we do not want to
  // translate part of a directory (like the foo part of foo-dir).
  path += "/";

  // In case a file was specified we still have to go through this:
  // Now convert any path found in the table back to the one desired:
  std::map<std::string, std::string>::const_iterator it;
  for (it = SystemTools::TranslationMap->begin();
       it != SystemTools::TranslationMap->end(); ++it) {
    // We need to check of the path is a substring of the other path
    if (path.find(it->first) == 0) {
      path = path.replace(0, it->first.size(), it->second);
    }
  }

  // Remove the trailing slash we added before.
  path.erase(path.end() - 1, path.end());
}