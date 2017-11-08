char *getpass_r(const char *prompt, char *buffer, size_t buflen)
{
  long sts;
  short chan;

  /* MSK, 23-JAN-2004, iosbdef.h wasn't in VAX V7.2 or CC 6.4  */
  /* distribution so I created this.  May revert back later to */
  /* struct _iosb iosb;                                        */
  struct _iosb
     {
     short int iosb$w_status; /* status     */
     short int iosb$w_bcnt;   /* byte count */
     int       unused;        /* unused     */
     } iosb;

  $DESCRIPTOR(ttdesc, "TT");

  buffer[0]='\0';
  sts = sys$assign(&ttdesc, &chan,0,0);
  if (sts & 1) {
    sts = sys$qiow(0, chan,
                   IO$_READPROMPT | IO$M_NOECHO,
                   &iosb, 0, 0, buffer, buflen, 0, 0,
                   prompt, strlen(prompt));

    if((sts & 1) && (iosb.iosb$w_status&1))
      buffer[iosb.iosb$w_bcnt] = '\0';

    sts = sys$dassgn(chan);
  }
  return buffer; /* we always return success */
}