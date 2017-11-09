static int sock_cb(CURL *e, curl_socket_t s, int what, void *cbp, void *sockp)
{
  fprintf(MSG_OUT, "\nsock_cb: socket=%d, what=%d, sockp=%p", s, what, sockp);

  GlobalInfo *g = (GlobalInfo*) cbp;
  int *actionp = (int *) sockp;
  const char *whatstr[] = { "none", "IN", "OUT", "INOUT", "REMOVE"};

  fprintf(MSG_OUT,
          "\nsocket callback: s=%d e=%p what=%s ", s, e, whatstr[what]);

  if(what == CURL_POLL_REMOVE) {
    fprintf(MSG_OUT, "\n");
    remsock(actionp, g);
  }
  else {
    if(!actionp) {
      fprintf(MSG_OUT, "\nAdding data: %s", whatstr[what]);
      addsock(s, e, what, g);
    }
    else {
      fprintf(MSG_OUT,
              "\nChanging action from %s to %s",
              whatstr[*actionp], whatstr[what]);
      setsock(actionp, s, e, what, *actionp, g);
    }
  }

  return 0;
}