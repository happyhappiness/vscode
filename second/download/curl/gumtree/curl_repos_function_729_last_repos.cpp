static void nak(int error)
{
  struct tftphdr *tp;
  int length;
  struct errmsg *pe;

  tp = &buf.hdr;
  tp->th_opcode = htons((unsigned short)opcode_ERROR);
  tp->th_code = htons((unsigned short)error);
  for(pe = errmsgs; pe->e_code >= 0; pe++)
    if(pe->e_code == error)
      break;
  if(pe->e_code < 0) {
    pe->e_msg = strerror(error - 100);
    tp->th_code = EUNDEF;   /* set 'undef' errorcode */
  }
  length = (int)strlen(pe->e_msg);

  /* we use memcpy() instead of strcpy() in order to avoid buffer overflow
   * report from glibc with FORTIFY_SOURCE */
  memcpy(tp->th_msg, pe->e_msg, length + 1);
  length += 5;
  if(swrite(peer, &buf.storage[0], length) != length)
    logmsg("nak: fail\n");
}