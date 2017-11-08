static ssize_t fullread(int filedes, void *buffer, size_t nbytes)
{
  int error;
  ssize_t rc;
  ssize_t nread = 0;

  do {
    rc = read(filedes, (unsigned char *)buffer + nread, nbytes - nread);

    if(got_exit_signal) {
      logmsg("signalled to die");
      return -1;
    }

    if(rc < 0) {
      error = ERRNO;
      if((error == EINTR) || (error == EAGAIN))
        continue;
      logmsg("unrecoverable read() failure: %s", strerror(error));
      return -1;
    }

    if(rc == 0) {
      logmsg("got 0 reading from stdin");
      return 0;
    }

    nread += rc;

  } while((size_t)nread < nbytes);

  if(verbose)
    logmsg("read %ld bytes", (long)nread);

  return nread;
}