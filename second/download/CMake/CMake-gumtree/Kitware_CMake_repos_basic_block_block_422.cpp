{
  SKIP_SPACE(buf); /* Skip leading spaces in both texts */
  SKIP_SPACE(s);

  if (*buf=='\0')
    {
      return (((*s)!='\0') ? NOMATCH : EXACT);
    } 
  else 
    {
      if (ccase)
	{
	  while(*s++ == *buf)
	    {
	      if (*buf++=='\0') return EXACT;
	    } 
	} 
      else 
	{
	  while(toupper(*s++)==toupper(*buf))
	    {
	      if (*buf++=='\0') return EXACT;
	    }
	}
    }
  /* At this location buf points to the first character where it no longer
     matches with s. So if only blanks are following, we have a partial
     match otherwise there is no match */
  SKIP_SPACE(buf);
  if (*buf) 
    return NOMATCH;

  /* If it happens that the reference buffer is at its end, the partial
     match is actually an exact match. */
  return ((s[-1]!='\0') ? PARTIAL : EXACT);
}