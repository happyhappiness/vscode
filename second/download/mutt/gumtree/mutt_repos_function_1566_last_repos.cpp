static struct maildir* maildir_sort (struct maildir* list, size_t len,
				     int (*cmp) (struct maildir *,
						 struct maildir *))
{
  struct maildir* left = list;
  struct maildir* right = list;
  size_t c = 0;

  if (!list || !list->next) 
  {
    return list;
  }

  if (len != (size_t)(-1) && len <= INS_SORT_THRESHOLD)
    return maildir_ins_sort (list, cmp);

  list = list->next;
  while (list && list->next) 
  {
    right = right->next;
    list = list->next->next;
    c++;
  }

  list = right;
  right = right->next;
  list->next = 0;

  left = maildir_sort (left, c, cmp);
  right = maildir_sort (right, c, cmp);
  return maildir_merge_lists (left, right, cmp);
}