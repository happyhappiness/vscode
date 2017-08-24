{
#ifdef O_CLOEXEC
    r = open(req->path, req->flags | O_CLOEXEC, req->mode);
    if (r >= 0)
      return r;
    if (errno != EINVAL)
      return r;
    no_cloexec_support = 1;
#endif  /* O_CLOEXEC */
  }