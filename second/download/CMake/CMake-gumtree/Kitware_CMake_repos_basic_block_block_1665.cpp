{
  /* Validate the flags.  */
  if (flags != 0) {
    return 0;
  }

  /* Forward to our internal implementation.  */
  return kwsysSystem__ParseUnixCommand(command, flags);
}