static void
gsk_free_handle(struct Curl_gsk_descriptor * p)

{
  struct gskstrlist * q;

  while((q = p->strlist)) {
    p->strlist = q;
    free((void *) q->asciistr);
    free(q);
  }
  free(p);
}