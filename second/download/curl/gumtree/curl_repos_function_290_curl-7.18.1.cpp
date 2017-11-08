static ssize_t fullwrite(int filedes, const void *buffer, size_t nbytes)
{
  int error;
  ssize_t wc;
  ssize_t nwrite = 0;

  do {
    wc = write(filedes, (unsigned char *)buffer + nwrite, nbytes - nwrite);

    if(got_exit_signal) {
      logmsg("signalled to die");
      return -1;
    }

    if(wc < 0) {
      error = ERRNO;
      if((error == EINTR) || (error == EAGAIN))
        continue;
      logmsg("unrecoverable write() failure: %s", strerror(error));
      return -1;
    }

    if(wc == 0) {
      logmsg("put 0 writing to stdout");
      return 0;
    }

    nwrite += wc;

  } while((size_t)nwrite < nbytes);

  if(verbose)
    logmsg("wrote %ld bytes", (long)nwrite);

  return nwrite;
}