static const char *mix_format_caps (REMAILER *r)
{
  static char capbuff[10];
  char *t = capbuff;
  
  if (r->caps & MIX_CAP_COMPRESS)
    *t++ = 'C';
  else
    *t++ = ' ';
  
  if (r->caps & MIX_CAP_MIDDLEMAN)
    *t++ = 'M';
  else
    *t++ = ' ';
  
  if (r->caps & MIX_CAP_NEWSPOST)
  {
    *t++ = 'N';
    *t++ = 'p';
  }
  else
  {
    *t++ = ' ';
    *t++ = ' ';
  }
   
  if (r->caps & MIX_CAP_NEWSMAIL)
  {
    *t++ = 'N';
    *t++ = 'm';
  }
  else
  {
    *t++ = ' ';
    *t++ = ' ';
  }
  
  *t = '\0';
  
  return capbuff;
}