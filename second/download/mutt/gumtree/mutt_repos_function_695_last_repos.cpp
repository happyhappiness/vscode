void hash_destroy (HASH **ptr, void (*destroy) (void *))
{
  int i;
  HASH *pptr;
  struct hash_elem *elem, *tmp;

  if (!ptr || !*ptr)
    return;

  pptr = *ptr;
  for (i = 0 ; i < pptr->nelem; i++)
  {
    for (elem = pptr->table[i]; elem; )
    {
      tmp = elem;
      elem = elem->next;
      if (destroy)
	destroy (tmp->data);
      if (pptr->strdup_keys)
        FREE (&tmp->key.strkey);
      FREE (&tmp);
    }
  }
  FREE (&pptr->table);
  FREE (ptr);		/* __FREE_CHECKED__ */
}