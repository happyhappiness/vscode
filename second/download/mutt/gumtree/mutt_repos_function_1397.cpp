BUFFER *mutt_buffer_new(void) {
  BUFFER *b;

  b = safe_malloc(sizeof(BUFFER));

  mutt_buffer_init(b);

  return b;
}