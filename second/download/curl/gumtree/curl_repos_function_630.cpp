static void recvtftp(struct testcase *test, struct formats *pf)
{
  ssize_t n, size;
  /* These are volatile to live through a siglongjmp */
  volatile unsigned short recvblock; /* block count */
  struct tftphdr * volatile rdp;     /* data buffer */
  struct tftphdr *rap;      /* ack buffer */

  recvblock = 0;
  rdp = w_init();
#if defined(HAVE_ALARM) && defined(SIGALRM)
  mysignal(SIGALRM, timer);
#endif
  rap = &ackbuf.hdr;
  do {
    timeout = 0;
    rap->th_opcode = htons((unsigned short)opcode_ACK);
    rap->th_block = htons(recvblock);
    recvblock++;
#ifdef HAVE_SIGSETJMP
    (void) sigsetjmp(timeoutbuf, 1);
#endif
send_ack:
    if (swrite(peer, &ackbuf.storage[0], 4) != 4) {
      logmsg("write: fail\n");
      goto abort;
    }
    write_behind(test, pf->f_convert);
    for ( ; ; ) {
#ifdef HAVE_ALARM
      alarm(rexmtval);
#endif
      n = sread(peer, rdp, PKTSIZE);
#ifdef HAVE_ALARM
      alarm(0);
#endif
      if(got_exit_signal)
        goto abort;
      if (n < 0) {                       /* really? */
        logmsg("read: fail\n");
        goto abort;
      }
      rdp->th_opcode = ntohs((unsigned short)rdp->th_opcode);
      rdp->th_block = ntohs(rdp->th_block);
      if (rdp->th_opcode == opcode_ERROR)
        goto abort;
      if (rdp->th_opcode == opcode_DATA) {
        if (rdp->th_block == recvblock) {
          break;                         /* normal */
        }
        /* Re-synchronize with the other side */
        (void) synchnet(peer);
        if (rdp->th_block == (recvblock-1))
          goto send_ack;                 /* rexmit */
      }
    }

    size = writeit(test, &rdp, (int)(n - 4), pf->f_convert);
    if (size != (n-4)) {                 /* ahem */
      if (size < 0)
        nak(errno + 100);
      else
        nak(ENOSPACE);
      goto abort;
    }
  } while (size == SEGSIZE);
  write_behind(test, pf->f_convert);

  rap->th_opcode = htons((unsigned short)opcode_ACK);  /* send the "final" ack */
  rap->th_block = htons(recvblock);
  (void) swrite(peer, &ackbuf.storage[0], 4);
#if defined(HAVE_ALARM) && defined(SIGALRM)
  mysignal(SIGALRM, justtimeout);        /* just abort read on timeout */
  alarm(rexmtval);
#endif
  /* normally times out and quits */
  n = sread(peer, &buf.storage[0], sizeof(buf.storage));
#ifdef HAVE_ALARM
  alarm(0);
#endif
  if(got_exit_signal)
    goto abort;
  if (n >= 4 &&                               /* if read some data */
      rdp->th_opcode == opcode_DATA &&        /* and got a data block */
      recvblock == rdp->th_block) {           /* then my last ack was lost */
    (void) swrite(peer, &ackbuf.storage[0], 4);  /* resend final ack */
  }
abort:
  return;
}