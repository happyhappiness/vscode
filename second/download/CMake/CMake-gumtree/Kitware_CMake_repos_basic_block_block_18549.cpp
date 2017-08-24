(*p == '/') {
      *p = 0;
      err = mkdir(tmp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
      if (err != 0 && errno != EEXIST)
        return err;
      *p = '/';
    }