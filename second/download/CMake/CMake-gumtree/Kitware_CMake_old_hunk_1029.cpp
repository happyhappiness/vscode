  const char* ret = getcwd(buf, len);
  if(!ret)
    {
    fprintf(stderr, "No current working directory\n");
    abort();
    }
  return ret;
