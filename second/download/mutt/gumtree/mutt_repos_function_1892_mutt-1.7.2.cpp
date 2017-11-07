static int msg_cache_clean_cb (const char* id, body_cache_t* bcache, void* data)
{
  unsigned int uv, uid, n;
  IMAP_DATA* idata = (IMAP_DATA*)data;

  if (sscanf (id, "%u-%u", &uv, &uid) != 2)
    return 0;

  /* bad UID */
  if (uv != idata->uid_validity)
    mutt_bcache_del (bcache, id);

  /* TODO: presort UIDs, walk in order */
  for (n = 0; n < idata->ctx->msgcount; n++)
  {
    if (uid == HEADER_DATA(idata->ctx->hdrs[n])->uid)
      return 0;
  }
  mutt_bcache_del (bcache, id);

  return 0;
}