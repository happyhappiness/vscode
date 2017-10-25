CURLcode 
Transfer(CURLconnect *c_conn,
         /* READ stuff */
	  int sockfd,		/* socket to read from or -1 */
	  int size,		/* -1 if unknown at this point */
	  bool getheader,	/* TRUE if header parsing is wanted */
	  long *bytecountp,	/* return number of bytes read or NULL */
          
          /* WRITE stuff */
          int writesockfd,      /* socket to write to, it may very well be
                                   the same we read from. -1 disables */
          long *writebytecountp /* return number of bytes written or NULL */
          )
{
  struct connectdata *conn = (struct connectdata *)c_conn;
  if(!conn)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  /* now copy all input parameters */
  conn->sockfd = sockfd;
  conn->size = size;
  conn->getheader = getheader;
  conn->bytecountp = bytecountp;
  conn->writesockfd = writesockfd;
  conn->writebytecountp = writebytecountp;

  return CURLE_OK;

}