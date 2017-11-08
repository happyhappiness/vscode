static
bool seed_enough(struct connectdata *conn, /* unused for now */
                 int nread)
{
  conn = NULL; /* to prevent compiler warnings */
#ifdef HAVE_RAND_STATUS
  nread = 0; /* to prevent compiler warnings */

  /* only available in OpenSSL 0.9.5a and later */
  if(RAND_status())
    return TRUE;
#else
  if(nread > 500)
    /* this is a very silly decision to make */
    return TRUE;
#endif
  return FALSE; /* not enough */
}