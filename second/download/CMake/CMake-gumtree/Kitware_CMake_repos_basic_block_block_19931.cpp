{
  int saved_errno;
  int err;

  saved_errno = errno;
  if (!uv_spinlock_trylock(&termios_spinlock))
    return -EBUSY;  /* In uv_tty_set_mode(). */

  err = 0;
  if (orig_termios_fd != -1)
    if (tcsetattr(orig_termios_fd, TCSANOW, &orig_termios))
      err = -errno;

  uv_spinlock_unlock(&termios_spinlock);
  errno = saved_errno;

  return err;
}