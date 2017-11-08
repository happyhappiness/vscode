static void recvtftp(struct testcase *test, struct formats *pf)
{
  struct tftphdr *dp;
  struct tftphdr *ap;    /* ack buffer */
  unsigned short block = 0;
  ssize_t n, size;
#if defined(HAVE_ALARM) && defined(SIGALRM)
  mysignal(SIGALRM, timer);
#endif
  dp = w_init();
  ap = (struct tftphdr *)ackbuf;
  do {
    timeout = 0;
    ap->th_opcode = htons((u_short)ACK);
    ap->th_block = htons((u_short)block);
    block++;
#ifdef HAVE_SIGSETJMP
    (void) sigsetjmp(timeoutbuf, 1);
#endif
send_ack:
    if (swrite(peer, ackbuf, 4) != 4) {
      logmsg("write: fail\n");
      goto abort;
    }
    write_behind(test, pf->f_convert);
    for ( ; ; ) {
#ifdef HAVE_ALARM
      alarm(rexmtval);
#endif
      n = sread(peer, dp, PKTSIZE);
#ifdef HAVE_ALARM
      alarm(0);
#endif
      if (n < 0) {                       /* really? */
        logmsg("read: fail\n");
        goto abort;
      }
      dp->th_opcode = ntohs((u_short)dp->th_opcode);
      dp->th_block = ntohs((u_short)dp->th_block);
      if (dp->th_opcode == ERROR)
        goto abort;
      if (dp->th_opcode == DATA) {
        if (dp->th_block == block) {
          break;                         /* normal */
        }
        /* Re-synchronize with the other side */
        (void) synchnet(peer);
        if (dp->th_block == (block-1))
          goto send_ack;                 /* rexmit */
      }
    }

    size = writeit(test, &dp, (int)(n - 4), pf->f_convert);
    if (size != (n-4)) {                 /* ahem */
      if (size < 0)
        nak(ERRNO + 100);
      else
        nak(ENOSPACE);
      goto abort;
    }
  } while (size == SEGSIZE);
  write_behind(test, pf->f_convert);

  ap->th_opcode = htons((u_short)ACK);   /* send the "final" ack */
  ap->th_block = htons((u_short)(block));
  (void) swrite(peer, ackbuf, 4);
#if defined(HAVE_ALARM) && defined(SIGALRM)
  mysignal(SIGALRM, justtimeout);        /* just abort read on timeout */
  alarm(rexmtval);
#endif
  n = sread(peer, buf, sizeof(buf));     /* normally times out and quits */
#ifdef HAVE_ALARM
  alarm(0);
#endif
  if (n >= 4 &&                          /* if read some data */
      dp->th_opcode == DATA &&           /* and got a data block */
      block == dp->th_block) {           /* then my last ack was lost */
    (void) swrite(peer, ackbuf, 4);      /* resend final ack */
  }
abort:
  return;
}