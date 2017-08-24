{
      wchar_t* work_dir = malloc(length * sizeof(wchar_t));
      if (!work_dir) {
        free(wdir);
        return 0;
      }
      if (!GetFullPathNameW(wdir, length, work_dir, 0)) {
        free(work_dir);
        free(wdir);
        return 0;
      }
      cp->WorkingDirectory = work_dir;
    }