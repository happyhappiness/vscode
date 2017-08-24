f(stat(filename, &st) == 0)
    if(S_ISREG(st.st_mode))
      return 1;