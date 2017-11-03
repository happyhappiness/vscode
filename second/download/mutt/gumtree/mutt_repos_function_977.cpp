static void include_header (int quote, FILE * ifp,
			    HEADER * hdr, FILE * ofp,
			    char *_prefix)
{
  int chflags = CH_DECODE;
  char prefix[SHORT_STRING];
  
  if (option (OPTWEED))
    chflags |= CH_WEED | CH_REORDER;

  if (quote)
  {
    if (_prefix)
      strfcpy (prefix, _prefix, sizeof (prefix));
    else if (!option (OPTTEXTFLOWED))
      _mutt_make_string (prefix, sizeof (prefix), NONULL (Prefix), 
			 Context, hdr, 0);
    else
      strfcpy (prefix, ">", sizeof (prefix));

    chflags |= CH_PREFIX;
  }
  
  mutt_copy_header (ifp, hdr, ofp, chflags, quote ? prefix : NULL);
}