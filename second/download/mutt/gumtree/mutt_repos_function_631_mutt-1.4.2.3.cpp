static void enriched_set_flags (const char *tag, struct enriched_state *stte)
{
  const char *tagptr = tag;
  int i, j;

  if (*tagptr == '/')
    tagptr++;
  
  for (i = 0, j = -1; EnrichedTags[i].tag_name; i++)
    if (ascii_strcasecmp (EnrichedTags[i].tag_name,tagptr) == 0)
    {
      j = EnrichedTags[i].index;
      break;
    }

  if (j != -1)
  {
    if (j == RICH_CENTER || j == RICH_FLUSHLEFT || j == RICH_FLUSHRIGHT)
      enriched_flush (stte, 1);

    if (*tag == '/')
    {
      if (stte->tag_level[j]) /* make sure not to go negative */
	stte->tag_level[j]--;
      if ((stte->s->flags & M_DISPLAY) && j == RICH_PARAM && stte->tag_level[RICH_COLOR])
      {
	stte->param[stte->param_used] = '\0';
	if (!ascii_strcasecmp(stte->param, "black"))
	{
	  enriched_puts("\033[30m", stte);
	}
	else if (!ascii_strcasecmp(stte->param, "red"))
	{
	  enriched_puts("\033[31m", stte);
	}
	else if (!ascii_strcasecmp(stte->param, "green"))
	{
	  enriched_puts("\033[32m", stte);
	}
	else if (!ascii_strcasecmp(stte->param, "yellow"))
	{
	  enriched_puts("\033[33m", stte);
	}
	else if (!ascii_strcasecmp(stte->param, "blue"))
	{
	  enriched_puts("\033[34m", stte);
	}
	else if (!ascii_strcasecmp(stte->param, "magenta"))
	{
	  enriched_puts("\033[35m", stte);
	}
	else if (!ascii_strcasecmp(stte->param, "cyan"))
	{
	  enriched_puts("\033[36m", stte);
	}
	else if (!ascii_strcasecmp(stte->param, "white"))
	{
	  enriched_puts("\033[37m", stte);
	}
      }
      if ((stte->s->flags & M_DISPLAY) && j == RICH_COLOR)
      {
	enriched_puts("\033[0m", stte);
      }

      /* flush parameter buffer when closing the tag */
      if (j == RICH_PARAM)
      {
	stte->param_used = 0;
	stte->param[0] = '\0';
      }
    }
    else
      stte->tag_level[j]++;

    if (j == RICH_EXCERPT)
      enriched_flush(stte, 1);
  }
}