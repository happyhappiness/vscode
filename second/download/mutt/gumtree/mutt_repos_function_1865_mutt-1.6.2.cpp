static int uid2msgno (IMAP_DATA* idata, unsigned int uid)
{
  int i;
  
  for (i = 0; i < idata->ctx->msgcount; i++)
  {
    HEADER* h = idata->ctx->hdrs[i];
    if (HEADER_DATA(h)->uid == uid)
      return i;
  }
  
  return -1;
}