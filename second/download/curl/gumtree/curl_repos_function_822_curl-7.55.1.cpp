SANITIZEcode truncate_dryrun(const char *path, const size_t truncate_pos)
{
  size_t len;

  if(!path)
    return SANITIZE_ERR_BAD_ARGUMENT;

  len = strlen(path);

  if(truncate_pos > len)
    return SANITIZE_ERR_BAD_ARGUMENT;

  if(!len || !truncate_pos)
    return SANITIZE_ERR_INVALID_PATH;

  if(strpbrk(&path[truncate_pos - 1], "\\/:"))
    return SANITIZE_ERR_INVALID_PATH;

  /* C:\foo can be truncated but C:\foo:ads can't */
  if(truncate_pos > 1) {
    const char *p = &path[truncate_pos - 1];
    do {
      --p;
      if(*p == ':')
        return SANITIZE_ERR_INVALID_PATH;
    } while(p != path && *p != '\\' && *p != '/');
  }

  return SANITIZE_ERR_OK;
}