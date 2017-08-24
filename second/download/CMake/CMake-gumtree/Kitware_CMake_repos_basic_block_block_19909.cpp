{
    if (tcgetattr(fd, &tty->orig_termios))
      return -errno;

    /* This is used for uv_tty_reset_mode() */
    uv_spinlock_lock(&termios_spinlock);
    if (orig_termios_fd == -1) {
      orig_termios = tty->orig_termios;
      orig_termios_fd = fd;
    }
    uv_spinlock_unlock(&termios_spinlock);
  }