SList *
slist_box (const void *userdata)
{
  SList *item = (SList *) malloc (sizeof *item);

  if (item)
    {
      item->next     = 0;
      item->userdata = userdata;
    }

  return item;
}