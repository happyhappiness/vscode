static int maildir_parse_dir(CONTEXT *ctx, struct maildir ***last,
			     const char *subdir, int *count)
{
  DIR *dirp;
  struct dirent *de;
  char buf[_POSIX_PATH_MAX];
  int is_old = 0;
  
  if(subdir)
  {
    snprintf(buf, sizeof(buf), "%s/%s", ctx->path, subdir);
    is_old = (mutt_strcmp("cur", subdir) == 0) && option(OPTMARKOLD);
  }
  else
    strfcpy(buf, ctx->path, sizeof(buf));
  
  if((dirp = opendir(buf)) == NULL)
    return -1;

  while ((de = readdir (dirp)) != NULL)
  {
    
    if ((ctx->magic == M_MH && !mh_valid_message(de->d_name)) || (ctx->magic == M_MAILDIR && *de->d_name == '.'))
      continue;
    
    /* FOO - really ignore the return value? */

    dprint(2, (debugfile, "%s:%d: parsing %s\n", __FILE__, __LINE__, de->d_name));
    maildir_parse_entry(ctx, last, subdir, de->d_name, count, is_old);
  }

  closedir(dirp);
  return 0;
}