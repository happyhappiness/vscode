static void mstate(struct SessionHandle *data, CURLMstate state
#ifdef DEBUGBUILD
                   , int lineno
#endif
)
{
#ifdef DEBUGBUILD
  long connection_id = -5000;
#endif
  CURLMstate oldstate = data->mstate;

  if(oldstate == state)
    /* don't bother when the new state is the same as the old state */
    return;

  data->mstate = state;

#ifdef DEBUGBUILD
  if(data->mstate >= CURLM_STATE_CONNECT_PEND &&
     data->mstate < CURLM_STATE_COMPLETED) {
    if(data->easy_conn)
      connection_id = data->easy_conn->connection_id;

    infof(data,
          "STATE: %s => %s handle %p; line %d (connection #%ld) \n",
          statename[oldstate], statename[data->mstate],
          (void *)data, lineno, connection_id);
  }
#endif
  if(state == CURLM_STATE_COMPLETED)
    /* changing to COMPLETED means there's one less easy handle 'alive' */
    data->multi->num_alive--;
}