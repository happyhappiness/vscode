static void maildir_delayed_parsing (CONTEXT * ctx, struct maildir **md,
			      progress_t *progress)
{ 
  struct maildir *p, *last = NULL;
  char fn[_POSIX_PATH_MAX];
  int count;
#if HAVE_DIRENT_D_INO
  int sort = 0;
#endif
#if USE_HCACHE
  header_cache_t *hc = NULL;
  void *data;
  struct timeval *when = NULL;
  struct stat lastchanged;
  int ret;
#endif

#if HAVE_DIRENT_D_INO
#define DO_SORT()	do { \
  if (!sort) \
  { \
    dprint (4, (debugfile, "maildir: need to sort %s by inode\n", ctx->path)); \
    p = maildir_sort (p, (size_t) -1, md_cmp_inode); \
    if (!last) \
      *md = p; \
    else \
      last->next = p; \
    sort = 1; \
    p = skip_duplicates (p, &last); \
    snprintf (fn, sizeof (fn), "%s/%s", ctx->path, p->h->path); \
  } \
} while(0)
#else
#define DO_SORT()	/* nothing */
#endif

#if USE_HCACHE
  hc = mutt_hcache_open (HeaderCache, ctx->path, NULL);
#endif

  for (p = *md, count = 0; p; p = p->next, count++)
   {
    if (! (p && p->h && !p->header_parsed))
     {
      last = p;
      continue;
    }

    if (!ctx->quiet && progress)
      mutt_progress_update (progress, count, -1);

    DO_SORT();

    snprintf (fn, sizeof (fn), "%s/%s", ctx->path, p->h->path);

#if USE_HCACHE
    if (option(OPTHCACHEVERIFY))
    {
       ret = stat(fn, &lastchanged);
    }
    else
    {
      lastchanged.st_mtime = 0;
      ret = 0;
    }

    if (ctx->magic == MUTT_MH)
      data = mutt_hcache_fetch (hc, p->h->path, strlen);
    else
      data = mutt_hcache_fetch (hc, p->h->path + 3, &maildir_hcache_keylen);
    when = (struct timeval *) data;

    if (data != NULL && !ret && lastchanged.st_mtime <= when->tv_sec)
    {
      p->h = mutt_hcache_restore ((unsigned char *)data, &p->h);
      if (ctx->magic == MUTT_MAILDIR)
	maildir_parse_flags (p->h, fn);
    }
    else
    {
#endif /* USE_HCACHE */

    if (maildir_parse_message (ctx->magic, fn, p->h->old, p->h))
    {
      p->header_parsed = 1;
#if USE_HCACHE
      if (ctx->magic == MUTT_MH)
	mutt_hcache_store (hc, p->h->path, p->h, 0, strlen, MUTT_GENERATE_UIDVALIDITY);
      else
	mutt_hcache_store (hc, p->h->path + 3, p->h, 0, &maildir_hcache_keylen, MUTT_GENERATE_UIDVALIDITY);
#endif
    } else
      mutt_free_header (&p->h);
#if USE_HCACHE
    }
    FREE (&data);
#endif
    last = p;
   }
#if USE_HCACHE
  mutt_hcache_close (hc);
#endif

#undef DO_SORT

  mh_sort_natural (ctx, md);
}