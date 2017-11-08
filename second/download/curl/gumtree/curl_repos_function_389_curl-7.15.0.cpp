static const char * ContentTypeForFilename (const char *filename,
                                            const char *prevtype)
{
  const char *contenttype = NULL;
  unsigned int i;
  /*
   * No type was specified, we scan through a few well-known
   * extensions and pick the first we match!
   */
  struct ContentType {
    const char *extension;
    const char *type;
  };
  static const struct ContentType ctts[]={
    {".gif",  "image/gif"},
    {".jpg",  "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".txt",  "text/plain"},
    {".html", "text/html"}
  };

  if(prevtype)
    /* default to the previously set/used! */
    contenttype = prevtype;
  else
    /* It seems RFC1867 defines no Content-Type to default to
       text/plain so we don't actually need to set this: */
    contenttype = HTTPPOST_CONTENTTYPE_DEFAULT;

  for(i=0; i<sizeof(ctts)/sizeof(ctts[0]); i++) {
    if(strlen(filename) >= strlen(ctts[i].extension)) {
      if(strequal(filename +
                  strlen(filename) - strlen(ctts[i].extension),
                  ctts[i].extension)) {
        contenttype = ctts[i].type;
        break;
      }
    }
  }
  /* we have a contenttype by now */
  return contenttype;
}