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
      FREE (&tmp);
    }
  }
  FREE (&pptr->table);
  FREE (ptr);		/* __FREE_CHECKED__ */
}