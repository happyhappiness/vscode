void hash_destroy (HASH **ptr, void (*destroy) (void *))
{
  int i;
  HASH *pptr = *ptr;
  struct hash_elem *elem, *tmp;

  for (i = 0 ; i < pptr->nelem; i++)
  {
    for (elem = pptr->table[i]; elem; )
    {
      tmp = elem;
      elem = elem->next;
      if (destroy)
	destroy (tmp->data);
      safe_free ((void **) &tmp);
    }
  }
  safe_free ((void **) &pptr->table);
  safe_free ((void **) ptr);
}