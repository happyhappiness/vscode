static void nak(int error)
{
  struct tftphdr *tp;
  int length;
  struct errmsg *pe;

  tp = (struct tftphdr *)buf;
  tp->th_opcode = htons((u_short)ERROR);
  tp->th_code = htons((u_short)error);
  for (pe = errmsgs; pe->e_code >= 0; pe++)
    if (pe->e_code == error)
      break;
  if (pe->e_code < 0) {
    pe->e_msg = strerror(error - 100);
    tp->th_code = EUNDEF;   /* set 'undef' errorcode */
  }
  strcpy(tp->th_msg, pe->e_msg);
  length = strlen(pe->e_msg);
  tp->th_msg[length] = '\0';
  length += 5;
  if (send(peer, buf, length, 0) != length)
    logmsg("nak: fail\n");
}