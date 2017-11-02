static int
cachestring(struct Curl_gsk_descriptor * p,
            const char * ebcdicbuf, int bufsize, const char * * buffer)

{
  int rc;
  char * asciibuf;
  struct gskstrlist * sp;

  for(sp = p->strlist; sp; sp = sp->next)
    if(sp->ebcdicstr == ebcdicbuf)
      break;
  if(!sp) {
    if(!(sp = (struct gskstrlist *) malloc(sizeof *sp)))
      return GSK_INSUFFICIENT_STORAGE;
    if(!(asciibuf = malloc(bufsize + 1))) {
      free(sp);
      return GSK_INSUFFICIENT_STORAGE;
    }
    QadrtConvertE2A(asciibuf, ebcdicbuf, bufsize, bufsize);
    asciibuf[bufsize] = '\0';
    sp->ebcdicstr = ebcdicbuf;
    sp->asciistr = asciibuf;
    sp->next = p->strlist;
    p->strlist = sp;
  }
  *buffer = sp->asciistr;
  return GSK_OK;
}