static void multistate(struct Curl_one_easy *easy, CURLMstate state)
{
#ifdef CURLDEBUG
  const char *statename[]={
    "INIT",
    "CONNECT",
    "WAITRESOLVE",
    "WAITCONNECT",
    "PROTOCONNECT",
    "DO",
    "DOING",
    "DO_MORE",
    "PERFORM",
    "DONE",
    "COMPLETED",
  };
  CURLMstate oldstate = easy->state;
#endif
  easy->state = state;

#ifdef CURLDEBUG
  infof(easy->easy_handle,
        "STATE: %s => %s handle %p: \n",
        statename[oldstate], statename[easy->state], (char *)easy);
#endif
}