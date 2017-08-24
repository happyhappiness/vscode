{
  int fout;
  if (!name) {
    return 1;
  }

  /* Close the existing descriptor.  */
  kwsysProcessCleanupDescriptor(p);

  /* Open a file for the pipe to write.  */
  if ((fout = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
    return 0;
  }

  /* Set close-on-exec flag on the pipe's end.  */
  if (fcntl(fout, F_SETFD, FD_CLOEXEC) < 0) {
    return 0;
  }

  /* Assign the replacement descriptor.  */
  *p = fout;
  return 1;
}