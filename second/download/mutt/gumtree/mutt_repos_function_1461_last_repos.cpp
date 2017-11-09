BUFFER *mutt_buffer_init (BUFFER *b) {
  memset(b, 0, sizeof(BUFFER));
  return b;
}