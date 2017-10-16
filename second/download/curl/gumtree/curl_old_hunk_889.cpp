  if(disabled) {
    /* if echo actually was disabled, add a newline */
    fputs("\n", stderr);
    (void)ttyecho(TRUE, fd); /* enable echo */
  }

  if(1 != fd)
    close(fd);

  return password; /* return pointer to buffer */
}

#endif /* DONE */
