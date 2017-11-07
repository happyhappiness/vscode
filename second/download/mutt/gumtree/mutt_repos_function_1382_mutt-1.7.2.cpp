void mutt_expand_fmt (char *dest, size_t destlen, const char *fmt, const char *src)
{
  const char *p;
  char *d;
  size_t slen;
  int found = 0;

  slen = mutt_strlen (src);
  destlen--;
  
  for (p = fmt, d = dest; destlen && *p; p++)
  {
    if (*p == '%') 
    {
      switch (p[1])
      {
	case '%':
	  *d++ = *p++;
	  destlen--;
	  break;
	case 's':
	  found = 1;
	  strfcpy (d, src, destlen + 1);
	  d       += destlen > slen ? slen : destlen;
	  destlen -= destlen > slen ? slen : destlen;
	  p++;
	  break;
	default:
	  *d++ = *p; 
	  destlen--;
	  break;
      }
    }
    else
    {
      *d++ = *p;
      destlen--;
    }
  }
  
  *d = '\0';
  
  if (!found && destlen > 0)
  {
    safe_strcat (dest, destlen, " ");
    safe_strcat (dest, destlen, src);
  }
  
}