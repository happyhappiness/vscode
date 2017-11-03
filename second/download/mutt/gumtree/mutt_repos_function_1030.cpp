static unsigned char *
dump_body(BODY * c, unsigned char *d, int *off, int convert)
{
  BODY nb;

  memcpy (&nb, c, sizeof (BODY));

  /* some fields are not safe to cache */
  nb.content = NULL;
  nb.charset = NULL;
  nb.next = NULL;
  nb.parts = NULL;
  nb.hdr = NULL;
  nb.aptr = NULL;

  lazy_realloc(&d, *off + sizeof (BODY));
  memcpy(d + *off, &nb, sizeof (BODY));
  *off += sizeof (BODY);

  d = dump_char(nb.xtype, d, off, 0);
  d = dump_char(nb.subtype, d, off, 0);

  d = dump_parameter(nb.parameter, d, off, convert);

  d = dump_char(nb.description, d, off, convert);
  d = dump_char(nb.form_name, d, off, convert);
  d = dump_char(nb.filename, d, off, convert);
  d = dump_char(nb.d_filename, d, off, convert);

  return d;
}