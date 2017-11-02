static void fifo_cb(EV_P_ struct ev_io *w, int revents)
{
  char s[1024];
  long int rv=0;
  int n=0;
  GlobalInfo *g = (GlobalInfo *)w->data;

  do
  {
    s[0]='\0';
    rv=fscanf(g->input, "%1023s%n", s, &n);
    s[n]='\0';
    if ( n && s[0] )
    {
      new_conn(s,g);  /* if we read a URL, go get it! */
    } else break;
  } while ( rv != EOF );
}