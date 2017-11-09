header_cache_t *
mutt_hcache_open(const char *path, const char *folder, hcache_namer_t namer)
{
  struct header_cache *h = safe_calloc(1, sizeof (struct header_cache));
  int (*hcache_open) (struct header_cache* h, const char* path);
  struct stat sb;

#if HAVE_QDBM
  hcache_open = hcache_open_qdbm;
#elif HAVE_TC
  hcache_open= hcache_open_tc;
#elif HAVE_KC
  hcache_open= hcache_open_kc;
#elif HAVE_GDBM
  hcache_open = hcache_open_gdbm;
#elif HAVE_DB4
  hcache_open = hcache_open_db4;
#elif HAVE_LMDB
  hcache_open = hcache_open_lmdb;
#endif

  /* Calculate the current hcache version from dynamic configuration */
  if (hcachever == 0x0) {
    union {
      unsigned char charval[16];
      unsigned int intval;
    } digest;
    struct md5_ctx ctx;
    REPLACE_LIST *spam;
    RX_LIST *nospam;

    hcachever = HCACHEVER;

    md5_init_ctx(&ctx);

    /* Seed with the compiled-in header structure hash */
    md5_process_bytes(&hcachever, sizeof(hcachever), &ctx);

    /* Mix in user's spam list */
    for (spam = SpamList; spam; spam = spam->next)
    {
      md5_process_bytes(spam->rx->pattern, strlen(spam->rx->pattern), &ctx);
      md5_process_bytes(spam->template, strlen(spam->template), &ctx);
    }

    /* Mix in user's nospam list */
    for (nospam = NoSpamList; nospam; nospam = nospam->next)
    {
      md5_process_bytes(nospam->rx->pattern, strlen(nospam->rx->pattern), &ctx);
    }

    /* Get a hash and take its bytes as an (unsigned int) hash version */
    md5_finish_ctx(&ctx, digest.charval);
    hcachever = digest.intval;
  }

#if HAVE_LMDB
  h->db = 0;
#else
  h->db = NULL;
#endif
  h->folder = get_foldername(folder);
  h->crc = hcachever;

  if (!path || path[0] == '\0')
  {
    FREE(&h->folder);
    FREE(&h);
    return NULL;
  }

  path = mutt_hcache_per_folder(path, h->folder, namer);

  if (!hcache_open (h, path))
    return h;
  else
  {
    /* remove a possibly incompatible version */
    if (!stat (path, &sb) && !unlink (path))
    {
      if (!hcache_open (h, path))
        return h;
    }
    FREE(&h->folder);
    FREE(&h);

    return NULL;
  }
}