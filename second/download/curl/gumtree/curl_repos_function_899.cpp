void Curl_conncontrol(struct connectdata *conn, bool closeit,
                      const char *reason)
{
#if defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) reason;
#endif

  infof(conn->data, "Marked for [%s]: %s\n", closeit?"closure":"keep alive",
        reason);

  conn->bits.close = closeit; /* the only place in the source code that should
                                 assign this bit */
}