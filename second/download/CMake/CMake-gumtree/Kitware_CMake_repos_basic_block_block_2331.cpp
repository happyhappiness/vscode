{
  if (!filename || !dir) {
    return false;
  }

  // Get the basename of 'filename'

  std::string filename_base = SystemTools::GetFilenameName(filename);

  // Check if 'dir' is really a directory
  // If win32 and matches something like C:, accept it as a dir

  std::string real_dir;
  if (!SystemTools::FileIsDirectory(dir)) {
#if defined(_WIN32)
    size_t dir_len = strlen(dir);
    if (dir_len < 2 || dir[dir_len - 1] != ':') {
#endif
      real_dir = SystemTools::GetFilenamePath(dir);
      dir = real_dir.c_str();
#if defined(_WIN32)
    }
#endif
  }

  // Try to find the file in 'dir'

  bool res = false;
  if (!filename_base.empty() && dir) {
    size_t dir_len = strlen(dir);
    int need_slash =
      (dir_len && dir[dir_len - 1] != '/' && dir[dir_len - 1] != '\\');

    std::string temp = dir;
    if (need_slash) {
      temp += "/";
    }
    temp += filename_base;

    if (SystemTools::FileExists(temp)) {
      res = true;
      filename_found = temp;
    }

    // If not found, we can try harder by appending part of the file to
    // to the directory to look inside.
    // Example: if we were looking for /foo/bar/yo.txt in /d1/d2, then
    // try to find yo.txt in /d1/d2/bar, then /d1/d2/foo/bar, etc.

    else if (try_filename_dirs) {
      std::string filename_dir(filename);
      std::string filename_dir_base;
      std::string filename_dir_bases;
      do {
        filename_dir = SystemTools::GetFilenamePath(filename_dir);
        filename_dir_base = SystemTools::GetFilenameName(filename_dir);
#if defined(_WIN32)
        if (filename_dir_base.empty() || *filename_dir_base.rbegin() == ':')
#else
        if (filename_dir_base.empty())
#endif
        {
          break;
        }

        filename_dir_bases = filename_dir_base + "/" + filename_dir_bases;

        temp = dir;
        if (need_slash) {
          temp += "/";
        }
        temp += filename_dir_bases;

        res = SystemTools::LocateFileInDir(filename_base.c_str(), temp.c_str(),
                                           filename_found, 0);

      } while (!res && !filename_dir_base.empty());
    }
  }

  return res;
}