static int
parse_object(BUFFER *buf, BUFFER *s, int *o, int *ql, BUFFER *err)
{
  int q_level = 0;
  char *eptr;
  
  if(!MoreArgs(s))
  {
    strfcpy(err->data, _("Missing arguments."), err->dsize);
    return -1;
  }
  
  mutt_extract_token(buf, s, 0);
  if(!mutt_strncmp(buf->data, "quoted", 6))
  {
    if(buf->data[6])
    {
      *ql = strtol(buf->data + 6, &eptr, 10);
      if(*eptr || q_level < 0)
      {
	snprintf(err->data, err->dsize, _("%s: no such object"), buf->data);
	return -1;
      }
    }
    else
      *ql = 0;
    
    *o = MT_COLOR_QUOTED;
  }
  else if ((*o = mutt_getvaluebyname (buf->data, Fields)) == -1)
  {
    snprintf (err->data, err->dsize, _("%s: no such object"), buf->data);
    return (-1);
  }

  return 0;
}