static void _state(struct connectdata *conn,
                   ftpstate newstate
#ifdef DEBUGBUILD
                   , int lineno
#endif
  )
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;

#if defined(DEBUGBUILD)

#if defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) lineno;
#else
  if(ftpc->state != newstate)
    infof(conn->data, "FTP %p (line %d) state change from %s to %s\n",
          (void *)ftpc, lineno, ftp_state_names[ftpc->state],
          ftp_state_names[newstate]);
#endif
#endif

  ftpc->state = newstate;
}