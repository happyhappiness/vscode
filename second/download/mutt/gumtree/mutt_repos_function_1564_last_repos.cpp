static struct maildir*  maildir_merge_lists (struct maildir *left,
					     struct maildir *right,
					     int (*cmp) (struct maildir *,
							 struct maildir *))
{
  struct maildir* head;
  struct maildir* tail;

  if (left && right) 
  {
    if (cmp (left, right) < 0)
    {
      head = left;
      left = left->next;
    }
    else 
    {
      head = right;
      right = right->next;
    }
  } 
  else 
  {
    if (left) 
      return left;
    else 
      return right;
  }
    
  tail = head;

  while (left && right) 
  {
    if (cmp (left, right) < 0)
    {
      tail->next = left;
      left = left->next;
    } 
    else 
    {
      tail->next = right;
      right = right->next;
    }
    tail = tail->next;
  }

  if (left) 
  {
    tail->next = left;
  }
  else
  {
    tail->next = right;
  }

  return head;
}