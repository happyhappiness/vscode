static void *
mutt_hcache_dump(header_cache_t *h, HEADER * header, int *off,
		 unsigned int uidvalidity, mutt_hcache_store_flags_t flags)
{
  unsigned char *d = NULL;
  HEADER nh;
  int convert = !Charset_is_utf8;

  *off = 0;
  d = lazy_malloc(sizeof (validate));

  if (flags & MUTT_GENERATE_UIDVALIDITY)
  {
    struct timeval now;
    gettimeofday(&now, NULL);
    memcpy(d, &now, sizeof (struct timeval));
  }
  else
    memcpy(d, &uidvalidity, sizeof (uidvalidity));
  *off += sizeof (validate);

  d = dump_int(h->crc, d, off);

  lazy_realloc(&d, *off + sizeof (HEADER));
  memcpy(&nh, header, sizeof (HEADER));

  /* some fields are not safe to cache */
  nh.tagged = 0;
  nh.changed = 0;
  nh.threaded = 0;
  nh.recip_valid = 0;
  nh.searched = 0;
  nh.matched = 0;
  nh.collapsed = 0;
  nh.limited = 0;
  nh.num_hidden = 0;
  nh.recipient = 0;
  nh.pair = 0;
  nh.attach_valid = 0;
  nh.path = NULL;
  nh.tree = NULL;
  nh.thread = NULL;
#ifdef MIXMASTER
  nh.chain = NULL;
#endif
#if defined USE_POP || defined USE_IMAP
  nh.data = NULL;
#endif

  memcpy(d + *off, &nh, sizeof (HEADER));
  *off += sizeof (HEADER);

  d = dump_envelope(nh.env, d, off, convert);
  d = dump_body(nh.content, d, off, convert);
  d = dump_char(nh.maildir_flags, d, off, convert);

  return d;
}