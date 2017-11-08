static apr_status_t pipeblock(apr_file_t *thepipe)
{
#if !BEOS_BLOCKING
      int fd_flags;

      fd_flags = fcntl(thepipe->filedes, F_GETFL, 0);
#  if defined(O_NONBLOCK)
      fd_flags &= ~O_NONBLOCK;
#  elif defined(O_NDELAY)
      fd_flags &= ~O_NDELAY;
#  elif defined(O_FNDELAY)
      fd_flags &= ~O_FNDELAY;
#  else 
      /* XXXX: this breaks things, but an alternative isn't obvious...*/
      return APR_ENOTIMPL;
#  endif
      if (fcntl(thepipe->filedes, F_SETFL, fd_flags) == -1) {
          return errno;
      }
#else /* BEOS_BLOCKING */

#  if BEOS_BONE /* This only works on BONE 0-6 */
      int on = 0;
      if (ioctl(thepipe->filedes, FIONBIO, &on, sizeof(on)) < 0) {
          return errno;
      }
#  else /* "classic" BeOS doesn't support this at all */
      return APR_ENOTIMPL;
#  endif 
 
#endif /* !BEOS_BLOCKING */

    thepipe->blocking = BLK_ON;
    return APR_SUCCESS;
}