(dir_len < 2 || dir[dir_len - 1] != ':') {
#endif
      real_dir = SystemTools::GetFilenamePath(dir);
      dir = real_dir.c_str();
#if defined(_WIN32)
    }