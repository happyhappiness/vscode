(tcsetattr(orig_termios_fd, TCSANOW, &orig_termios))
      err = -errno