static int maildir_parse_entry(CONTEXT *ctx, struct maildir ***last,
				const char *subdir, const char *fname,
				int *count, int is_old)
{
  struct maildir *entry;
  HEADER *h;
  char buf[_POSIX_PATH_MAX];

  if(subdir)
    snprintf(buf, sizeof(buf), "%s/%s/%s", ctx->path, subdir, fname);
  else
    snprintf(buf, sizeof(buf), "%s/%s", ctx->path, fname);
  
  if((h = maildir_parse_message(ctx->magic, buf, is_old)) != NULL)
  {
    if(count)
    {
      (*count)++;  
      if (!ctx->quiet && ReadInc && ((*count % ReadInc) == 0 || *count == 1))
	mutt_message (_("Reading %s... %d"), ctx->path, *count);
    }

    if (subdir)
    {
      snprintf (buf, sizeof (buf), "%s/%s", subdir, fname);
      h->path = safe_strdup (buf);
    }
    else
      h->path = safe_strdup (fname);
    
    entry = safe_calloc(sizeof(struct maildir), 1);
    entry->h = h;
    **last = entry;
    *last = &entry->next;
    
    return 0;
  }
  
  return -1;
}