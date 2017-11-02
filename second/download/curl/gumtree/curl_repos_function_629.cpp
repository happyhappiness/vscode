static void sendtftp(struct testcase *test, struct formats *pf)
{
  int size;
  ssize_t n;
  /* This is volatile to live through a siglongjmp */
  volatile unsigned short sendblock; /* block count */
  struct tftphdr *sdp;      /* data buffer */
  struct tftphdr *sap;      /* ack buffer */

  sendblock = 1;
#if defined(HAVE_ALARM) && defined(SIGALRM)
  mysignal(SIGALRM, timer);
#endif
  sdp = r_init();
  sap = &ackbuf.hdr;
  do {
    size = readit(test, &sdp, pf->f_convert);
    if (size < 0) {
      nak(errno + 100);
      return;
    }
    sdp->th_opcode = htons((unsigned short)opcode_DATA);
    sdp->th_block = htons(sendblock);
    timeout = 0;
#ifdef HAVE_SIGSETJMP
    (void) sigsetjmp(timeoutbuf, 1);
#endif
    if(test->writedelay) {
      logmsg("Pausing %d seconds before %d bytes", test->writedelay,
             size);
      wait_ms(1000*test->writedelay);
    }

    send_data:
    if (swrite(peer, sdp, size + 4) != size + 4) {
      logmsg("write");
      return;
    }
    read_ahead(test, pf->f_convert);
    for ( ; ; ) {
#ifdef HAVE_ALARM
      alarm(rexmtval);        /* read the ack */
#endif
      n = sread(peer, &ackbuf.storage[0], sizeof(ackbuf.storage));
#ifdef HAVE_ALARM
      alarm(0);
#endif
      if(got_exit_signal)
        return;
      if (n < 0) {
        logmsg("read: fail");
        return;
      }
      sap->th_opcode = ntohs((unsigned short)sap->th_opcode);
      sap->th_block = ntohs(sap->th_block);

      if (sap->th_opcode == opcode_ERROR) {
        logmsg("got ERROR");
        return;
      }

      if (sap->th_opcode == opcode_ACK) {
        if (sap->th_block == sendblock) {
          break;
        }
        /* Re-synchronize with the other side */
        (void) synchnet(peer);
        if (sap->th_block == (sendblock-1)) {
          goto send_data;
        }
      }

    }
    sendblock++;
  } while (size == SEGSIZE);
}