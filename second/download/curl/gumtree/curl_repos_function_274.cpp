static void
thdbufdestroy(void * private)

{
  if(private) {
    buffer_t * p = (buffer_t *) private;
    localkey_t i;

    for(i = (localkey_t) 0; i < LK_LAST; i++) {
      if(p->buf)
        free(p->buf);

      p++;
      }

    free(private);
    }
}