{
    size = strlen(argv[i]) + 1;
    memcpy(s, argv[i], size);
    new_argv[i] = s;
    s += size;
  }