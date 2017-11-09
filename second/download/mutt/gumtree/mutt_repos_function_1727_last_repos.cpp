void mutt_check_lookup_list (BODY *b, char *type, int len)
{
  LIST *t = MimeLookupList;
  int i;

  for (; t; t = t->next) {
    i = mutt_strlen (t->data) - 1;
    if ((i > 0 && t->data[i-1] == '/' && t->data[i] == '*' && 
	 ascii_strncasecmp (type, t->data, i) == 0) ||
	ascii_strcasecmp (type, t->data) == 0) {

    BODY tmp = {0};
    int n;
    if ((n = mutt_lookup_mime_type (&tmp, b->filename)) != TYPEOTHER) {
      snprintf (type, len, "%s/%s",
                n == TYPEAUDIO ? "audio" :
                n == TYPEAPPLICATION ? "application" :
                n == TYPEIMAGE ? "image" :
                n == TYPEMESSAGE ? "message" :
                n == TYPEMODEL ? "model" :
                n == TYPEMULTIPART ? "multipart" :
                n == TYPETEXT ? "text" :
                n == TYPEVIDEO ? "video" : "other",
                tmp.subtype);
      dprint(1, (debugfile, "mutt_check_lookup_list: \"%s\" -> %s\n", 
        b->filename, type));
    }
    if (tmp.subtype) 
      FREE (&tmp.subtype);
    if (tmp.xtype) 
      FREE (&tmp.xtype);
    }
  }
}