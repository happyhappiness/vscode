static void cmd_parse_search (IMAP_DATA* idata, const char* s)
{
  unsigned int uid;
  int msgno;

  dprint (2, (debugfile, "Handling SEARCH\n"));

  while ((s = imap_next_word ((char*)s)) && *s != '\0')
  {
    uid = atoi (s);
    msgno = uid2msgno (idata, uid);
    
    if (msgno >= 0)
      idata->ctx->hdrs[uid2msgno (idata, uid)]->matched = 1;
  }
}