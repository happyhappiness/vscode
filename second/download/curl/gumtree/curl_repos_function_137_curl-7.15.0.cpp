static int tftp(struct testcase *test, struct tftphdr *tp, int size)
{
  char *cp;
  int first = 1, ecode;
  struct formats *pf;
  char *filename, *mode = NULL;

  /* store input protocol */
  fprintf(test->server, "opcode: %x\n", tp->th_opcode);

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
    return 3;
  }
  if (first) {
    mode = ++cp;
    first = 0;
    goto again;
  }
  /* store input protocol */
  fprintf(test->server, "filename: %s\n", filename);

  for (cp = mode; *cp; cp++)
    if (isupper((int)*cp))
      *cp = tolower((int)*cp);

  /* store input protocol */
  fprintf(test->server, "mode: %s\n", mode);

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