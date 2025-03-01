static
void latin1_toUtf16(const ENCODING *enc,
		    const char **fromP, const char *fromLim,
		    unsigned short **toP, const unsigned short *toLim)
{
  while (*fromP != fromLim && *toP != toLim)
    *(*toP)++ = (unsigned char)*(*fromP)++;
}