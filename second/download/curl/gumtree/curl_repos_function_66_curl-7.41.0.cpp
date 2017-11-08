static int sock_cb(CURL *e, curl_socket_t s, int what, void *cbp, void *sockp)
{
  DPRINT("%s e %p s %i what %i cbp %p sockp %p\n",
         __PRETTY_FUNCTION__, e, s, what, cbp, sockp);

  GlobalInfo *g = (GlobalInfo*) cbp;
  SockInfo *fdp = (SockInfo*) sockp;
  const char *whatstr[]={ "none", "IN", "OUT", "INOUT", "REMOVE"};

  fprintf(MSG_OUT,
          "socket callback: s=%d e=%p what=%s ", s, e, whatstr[what]);
  if ( what == CURL_POLL_REMOVE )
  {
    fprintf(MSG_OUT, "\n");
    remsock(fdp, g);
  } else
  {
    if ( !fdp )
    {
      fprintf(MSG_OUT, "Adding data: %s\n", whatstr[what]);
      addsock(s, e, what, g);
    } else
    {
      fprintf(MSG_OUT,
              "Changing action from %s to %s\n",
              whatstr[fdp->action], whatstr[what]);
      setsock(fdp, s, e, what, g);
    }
  }
  return 0;
}