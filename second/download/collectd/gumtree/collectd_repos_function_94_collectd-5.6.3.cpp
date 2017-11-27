lt_dlloader
lt_dlloader_next (lt_dlloader loader)
{
  SList *item = (SList *) loader;
  return (lt_dlloader) (item ? item->next : loaders);
}