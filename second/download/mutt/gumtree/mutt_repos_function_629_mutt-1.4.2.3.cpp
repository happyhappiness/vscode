static void enriched_putc (int c, struct enriched_state *stte)
{
  if (stte->tag_level[RICH_PARAM]) 
  {
    if (stte->tag_level[RICH_COLOR]) 
    {
      if (stte->param_used + 1 >= stte->param_len)
	safe_realloc ((void **) &stte->param, (stte->param_len += STRING));

      stte->param[stte->param_used++] = c;
    }
    return; /* nothing to do */
  }

  /* see if more space is needed (plus extra for possible rich characters) */
  if (stte->buff_len < stte->buff_used + 3)
  {
    stte->buff_len += LONG_STRING;
    safe_realloc ((void **) &stte->buffer, stte->buff_len + 1);
  }

  if ((!stte->tag_level[RICH_NOFILL] && ISSPACE (c)) || c == '\0' )
  {
    if (c == '\t')
      stte->word_len += 8 - (stte->line_len + stte->word_len) % 8;
    else
      stte->word_len++;
    
    stte->buffer[stte->buff_used++] = c;
    enriched_flush (stte, 0);
  }
  else
  {
    if (stte->s->flags & M_DISPLAY)
    {
      if (stte->tag_level[RICH_BOLD])
      {
	stte->buffer[stte->buff_used++] = c;
	stte->buffer[stte->buff_used++] = '\010';
	stte->buffer[stte->buff_used++] = c;
      }
      else if (stte->tag_level[RICH_UNDERLINE])
      {

	stte->buffer[stte->buff_used++] = '_';
	stte->buffer[stte->buff_used++] = '\010';
	stte->buffer[stte->buff_used++] = c;
      }
      else if (stte->tag_level[RICH_ITALIC])
      {
	stte->buffer[stte->buff_used++] = c;
	stte->buffer[stte->buff_used++] = '\010';
	stte->buffer[stte->buff_used++] = '_';
      }
      else
      {
	stte->buffer[stte->buff_used++] = c;
      }
    }
    else
    {
      stte->buffer[stte->buff_used++] = c;
    }
    stte->word_len++;
  }
}