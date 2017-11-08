static void multistate(struct Curl_one_easy *easy, CURLMstate state)
{
#ifdef CURLDEBUG
  long connectindex = -5000;
#endif
  CURLMstate oldstate = easy->state;

  if(oldstate == state)
    /* don't bother when the new state is the same as the old state */
    return;

  easy->state = state;

#ifdef CURLDEBUG
  if(easy->state > CURLM_STATE_CONNECT &&
     easy->state < CURLM_STATE_COMPLETED)
    connectindex = easy->easy_conn->connectindex;

  infof(easy->easy_handle,
        "STATE: %s => %s handle %p; (connection #%ld) \n",
        statename[oldstate], statename[easy->state],
        (char *)easy, connectindex);
#endif
  if(state == CURLM_STATE_COMPLETED)
    /* changing to COMPLETED means there's one less easy handle 'alive' */
    easy->easy_handle->multi->num_alive--;
}