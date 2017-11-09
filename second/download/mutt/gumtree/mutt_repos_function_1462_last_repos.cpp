BUFFER *mutt_buffer_from (char *seed) {
  BUFFER *b;

  if (!seed)
    return NULL;

  b = mutt_buffer_new ();
  b->data = safe_strdup(seed);
  b->dsize = mutt_strlen(seed);
  b->dptr = (char *) b->data + b->dsize;
  return b;
}