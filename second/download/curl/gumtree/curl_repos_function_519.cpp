static void state(struct connectdata *conn,
                  ftpstate state)
{
#ifdef CURLDEBUG
  /* for debug purposes */
  const char *names[]={
    "STOP",
    "WAIT220",
    "AUTH",
    "USER",
    "PASS",
    "ACCT",
    "PBSZ",
    "PROT",
    "PWD",
    "QUOTE",
    "RETR_PREQUOTE",
    "STOR_PREQUOTE",
    "POSTQUOTE",
    "CWD",
    "MKD",
    "MDTM",
    "TYPE",
    "LIST_TYPE",
    "RETR_TYPE",
    "STOR_TYPE",
    "SIZE",
    "RETR_SIZE",
    "STOR_SIZE",
    "REST",
    "RETR_REST",
    "PORT",
    "PASV",
    "LIST",
    "RETR",
    "STOR",
    "QUIT"
  };
#endif
  struct FTP *ftp = conn->proto.ftp;
#ifdef CURLDEBUG
  if(ftp->state != state)
    infof(conn->data, "FTP %p state change from %s to %s\n",
          ftp, names[ftp->state], names[state]);
#endif
  ftp->state = state;
}