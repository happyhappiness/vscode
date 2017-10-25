static void time2str(char *r, long t)
{
  long h;
  if(!t) {
    strcpy(r, "--:--:--");
    return;
  }
  h = (t/3600);
  if(h <= 99) {
    long m = (t-(h*3600))/60;
    long s = (t-(h*3600)-(m*60));
    snprintf(r, 9, "%2ld:%02ld:%02ld",h,m,s);
  }
  else {
    /* this equals to more than 99 hours, switch to a more suitable output
       format to fit within the limits. */
    if(h/24 <= 999)
      snprintf(r, 9, "%3ldd %02ldh", h/24, h-(h/24)*24);
    else
      snprintf(r, 9, "%7ldd", h/24);
  }
}