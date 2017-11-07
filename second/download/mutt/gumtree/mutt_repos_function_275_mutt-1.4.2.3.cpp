BUFFY *mutt_find_mailbox (const char *path)
{
  BUFFY *tmp = NULL;
  struct stat sb;
  struct stat tmp_sb;
  
  if (stat (path,&sb) != 0)
    return NULL;

  for (tmp = Incoming; tmp; tmp = tmp->next)
  {
    if (stat (tmp->path,&tmp_sb) ==0 && 
	sb.st_dev == tmp_sb.st_dev && sb.st_ino == tmp_sb.st_ino)
      break;
  }
  return tmp;
}