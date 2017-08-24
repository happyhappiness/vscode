{
    uv__free(buf);
    buf = uv__malloc(bufsize);

    if (buf == NULL)
      return -ENOMEM;

    r = getpwuid_r(uid, &pw, buf, bufsize, &result);

    if (r != ERANGE)
      break;

    bufsize *= 2;
  }