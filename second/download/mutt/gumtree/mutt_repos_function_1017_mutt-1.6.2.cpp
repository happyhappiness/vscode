HEADER *
mutt_hcache_restore(const unsigned char *d, HEADER ** oh)
{
  int off = 0;
  HEADER *h = mutt_new_header();
  int convert = !Charset_is_utf8;

  /* skip validate */
  off += sizeof (validate);

  /* skip crc */
  off += sizeof (unsigned int);

  memcpy(h, d + off, sizeof (HEADER));
  off += sizeof (HEADER);

  h->env = mutt_new_envelope();
  restore_envelope(h->env, d, &off, convert);

  h->content = mutt_new_body();
  restore_body(h->content, d, &off, convert);

  restore_char(&h->maildir_flags, d, &off, convert);

  /* this is needed for maildir style mailboxes */
  if (oh)
  {
    h->old = (*oh)->old;
    h->path = safe_strdup((*oh)->path);
    mutt_free_header(oh);
  }

  return h;
}