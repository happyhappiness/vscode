static void sendtftp(struct testcase *test, struct formats *pf)
{
  struct tftphdr *dp;
  struct tftphdr *ap;    /* ack packet */
  unsigned short block = 1;
  int size, n;

  mysignal(SIGALRM, timer);
  dp = r_init();
  ap = (struct tftphdr *)ackbuf;
  do {
    size = readit(test, &dp, pf->f_convert);
    if (size < 0) {
      nak(errno + 100);
      return;
    }
    dp->th_opcode = htons((u_short)DATA);
    dp->th_block = htons((u_short)block);
    timeout = 0;
    (void) sigsetjmp(timeoutbuf, 1);

    send_data:
    if (send(peer, dp, size + 4, 0) != size + 4) {
      logmsg("write\n");
      return;
    }
    read_ahead(test, pf->f_convert);
    for ( ; ; ) {
      alarm(rexmtval);        /* read the ack */
      n = recv(peer, ackbuf, sizeof (ackbuf), 0);
      alarm(0);
      if (n < 0) {
        logmsg("read: fail\n");
        return;
      }
      ap->th_opcode = ntohs((u_short)ap->th_opcode);
      ap->th_block = ntohs((u_short)ap->th_block);

      if (ap->th_opcode == ERROR) {
        logmsg("got ERROR");
        return;
      }

      if (ap->th_opcode == ACK) {
        if (ap->th_block == block) {
          break;
        }
        /* Re-synchronize with the other side */
        (void) synchnet(peer);
        if (ap->th_block == (block -1)) {
          goto send_data;
        }
      }

    }
    block++;
  } while (size == SEGSIZE);
}