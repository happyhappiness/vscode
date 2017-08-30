  const char* ret = _getcwd(buf, len);

  if(!ret)

    {

    fprintf(stderr, "No current working directory.\n");

    abort();

    }

  // make sure the drive letter is capital

