static int mix_get_caps (const char *capstr)
{
  int caps = 0;

  while (*capstr)
  {
    switch (*capstr)
    {
      case 'C':
      	caps |= MIX_CAP_COMPRESS;
        break;
      
      case 'M':
        caps |= MIX_CAP_MIDDLEMAN;
        break;
      
      case 'N':
      {
	switch (*++capstr)
	{
	  case 'm':
	    caps |= MIX_CAP_NEWSMAIL;
	    break;
	  
	  case 'p':
	    caps |= MIX_CAP_NEWSPOST;
	    break;
	  
	}
      }
    }
    
    if (*capstr) capstr++;
  }
  
  return caps;
}