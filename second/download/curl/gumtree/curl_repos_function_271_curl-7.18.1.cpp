static int tftp(struct testcase *test, struct tftphdr *tp, int size)
{
  char *cp;
  int first = 1, ecode;
  struct formats *pf;
  char *filename, *mode = NULL;
  int error;
  FILE *server;

  /* Open request dump file. */
  server = fopen(REQUEST_DUMP, "ab");
  if(!server) {
    error = ERRNO;
    logmsg("fopen() failed with error: %d %s", error, strerror(error));
    logmsg("Error opening file: %s", REQUEST_DUMP);
    return -1;
  }

  /* store input protocol */
  fprintf(server, "opcode: %x\n", tp->th_opcode);

  cp = (char *)&tp->th_stuff;
  filename = cp;
again:
  while (cp < buf + size) {
    if (*cp == '\0')
      break;
    cp++;
  }
  if (*cp) {
    nak(EBADOP);
    fclose(server);
    return 3;
  }
  if (first) {
    mode = ++cp;
    first = 0;
    goto again;
  }
  /* store input protocol */
  fprintf(server, "filename: %s\n", filename);

  for (cp = mode; *cp; cp++)
    if(ISUPPER(*cp))
      *cp = (char)tolower((int)*cp);

  /* store input protocol */
  fprintf(server, "mode: %s\n", mode);
  fclose(server);

  for (pf = formats; pf->f_mode; pf++)
    if (strcmp(pf->f_mode, mode) == 0)
      break;
  if (!pf->f_mode) {
    nak(EBADOP);
    return 2;
  }
  ecode = validate_access(test, filename, tp->th_opcode);
  if (ecode) {
    nak(ecode);
    return 1;
  }
  if (tp->th_opcode == WRQ)
    recvtftp(test, pf);
  else
    sendtftp(test, pf);

  return 0;
}