{
  /* Close the existing descriptor.  */
  kwsysProcessCleanupDescriptor(p);

  /* Set close-on-exec flag on the pipe's ends.  The proper end will
     be dup2-ed into the standard descriptor number after fork but
     before exec.  */
  if ((fcntl(des[0], F_SETFD, FD_CLOEXEC) < 0) ||
      (fcntl(des[1], F_SETFD, FD_CLOEXEC) < 0)) {
    return 0;
  }

  /* Assign the replacement descriptor.  */
  *p = des[1];
  return 1;
}