{
#if defined(__linux__)
  static int no_preadv;
#endif
  ssize_t result;

#if defined(_AIX)
  struct stat buf;
  if(fstat(req->file, &buf))
    return -1;
  if(S_ISDIR(buf.st_mode)) {
    errno = EISDIR;
    return -1;
  }
#endif /* defined(_AIX) */
  if (req->off < 0) {
    if (req->nbufs == 1)
      result = read(req->file, req->bufs[0].base, req->bufs[0].len);
    else
      result = readv(req->file, (struct iovec*) req->bufs, req->nbufs);
  } else {
    if (req->nbufs == 1) {
      result = pread(req->file, req->bufs[0].base, req->bufs[0].len, req->off);
      goto done;
    }

#if HAVE_PREADV
    result = preadv(req->file, (struct iovec*) req->bufs, req->nbufs, req->off);
#else
# if defined(__linux__)
    if (no_preadv) retry:
# endif
    {
      off_t nread;
      size_t index;

      nread = 0;
      index = 0;
      result = 1;
      do {
        if (req->bufs[index].len > 0) {
          result = pread(req->file,
                         req->bufs[index].base,
                         req->bufs[index].len,
                         req->off + nread);
          if (result > 0)
            nread += result;
        }
        index++;
      } while (index < req->nbufs && result > 0);
      if (nread > 0)
        result = nread;
    }
# if defined(__linux__)
    else {
      result = uv__preadv(req->file,
                          (struct iovec*)req->bufs,
                          req->nbufs,
                          req->off);
      if (result == -1 && errno == ENOSYS) {
        no_preadv = 1;
        goto retry;
      }
    }
# endif
#endif
  }

done:
  return result;
}