static int do_tftp(struct testcase *test, struct tftphdr *tp, ssize_t size)
{
  char *cp;
  int first = 1, ecode;
  struct formats *pf;
  char *filename, *mode = NULL;
  int error;
  FILE *server;
#ifdef USE_WINSOCK
  DWORD recvtimeout, recvtimeoutbak;
#endif
  const char *option = "mode"; /* mode is implicit */
  int toggle = 1;

  /* Open request dump file. */
  server = fopen(REQUEST_DUMP, "ab");
  if(!server) {
    error = errno;
    logmsg("fopen() failed with error: %d %s", error, strerror(error));
    logmsg("Error opening file: %s", REQUEST_DUMP);
    return -1;
  }

  /* store input protocol */
  fprintf(server, "opcode: %x\n", tp->th_opcode);

  cp = (char *)&tp->th_stuff;
  filename = cp;
  do {
    bool endofit = true;
    while(cp < &buf.storage[size]) {
      if(*cp == '\0') {
        endofit = false;
        break;
      }
      cp++;
    }
    if(endofit)
      /* no more options */
      break;

    /* before increasing pointer, make sure it is still within the legal
       space */
    if((cp + 1) < &buf.storage[size]) {
      ++cp;
      if(first) {
        /* store the mode since we need it later */
        mode = cp;
        first = 0;
      }
      if(toggle)
        /* name/value pair: */
        fprintf(server, "%s: %s\n", option, cp);
      else {
        /* store the name pointer */
        option = cp;
      }
      toggle ^= 1;
    }
    else
      /* No more options */
      break;
  } while(1);

  if(*cp) {
    nak(EBADOP);
    fclose(server);
    return 3;
  }

  /* store input protocol */
  fprintf(server, "filename: %s\n", filename);

  for(cp = mode; cp && *cp; cp++)
    if(ISUPPER(*cp))
      *cp = (char)tolower((int)*cp);

  /* store input protocol */
  fclose(server);

  for(pf = formata; pf->f_mode; pf++)
    if(strcmp(pf->f_mode, mode) == 0)
      break;
  if(!pf->f_mode) {
    nak(EBADOP);
    return 2;
  }
  ecode = validate_access(test, filename, tp->th_opcode);
  if(ecode) {
    nak(ecode);
    return 1;
  }

#ifdef USE_WINSOCK
  recvtimeout = sizeof(recvtimeoutbak);
  getsockopt(peer, SOL_SOCKET, SO_RCVTIMEO,
             (char *)&recvtimeoutbak, (int *)&recvtimeout);
  recvtimeout = TIMEOUT*1000;
  setsockopt(peer, SOL_SOCKET, SO_RCVTIMEO,
             (const char *)&recvtimeout, sizeof(recvtimeout));
#endif

  if(tp->th_opcode == opcode_WRQ)
    recvtftp(test, pf);
  else
    sendtftp(test, pf);

#ifdef USE_WINSOCK
  recvtimeout = recvtimeoutbak;
  setsockopt(peer, SOL_SOCKET, SO_RCVTIMEO,
             (const char *)&recvtimeout, sizeof(recvtimeout));
#endif

  return 0;
}