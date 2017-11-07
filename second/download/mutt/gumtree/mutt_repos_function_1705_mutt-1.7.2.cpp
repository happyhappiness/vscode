static int parse_group_context (group_context_t **ctx, BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  while (!mutt_strcasecmp (buf->data, "-group"))
  {
    if (!MoreArgs (s)) 
    {
      strfcpy (err->data, _("-group: no group name"), err->dsize);
      goto bail;
    }
    
    mutt_extract_token (buf, s, 0);

    mutt_group_context_add (ctx, mutt_pattern_group (buf->data));
    
    if (!MoreArgs (s))
    {
      strfcpy (err->data, _("out of arguments"), err->dsize);
      goto bail;
    }
    
    mutt_extract_token (buf, s, 0);
  }
  
  return 0;
  
  bail:
  mutt_group_context_destroy (ctx);
  return -1;
}