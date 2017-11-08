static void
thdbufdestroy(void * private)

{
  localkey_t i;
  buffer_t * p;

  if(private) {
    p = (buffer_t *) private;

    for(i = (localkey_t) 0; i < LK_LAST; i++) {
      if(p->buf)
        free(p->buf);

      p++;
      }

    free(private);
    }
}