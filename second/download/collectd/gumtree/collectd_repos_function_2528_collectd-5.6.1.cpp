int c_heap_insert (c_heap_t *h, void *ptr)
{
  size_t index;

  if ((h == NULL) || (ptr == NULL))
    return (-EINVAL);

  pthread_mutex_lock (&h->lock);

  assert (h->list_len <= h->list_size);
  if (h->list_len == h->list_size)
  {
    void **tmp;

    tmp = realloc (h->list, (h->list_size + 16) * sizeof (*h->list));
    if (tmp == NULL)
    {
      pthread_mutex_unlock (&h->lock);
      return (-ENOMEM);
    }

    h->list = tmp;
    h->list_size += 16;
  }

  /* Insert the new node as a leaf. */
  index = h->list_len;
  h->list[index] = ptr;
  h->list_len++;

  /* Reorganize the heap from bottom up. */
  reheap (h, /* parent of this node = */ (index - 1) / 2, DIR_UP);

  pthread_mutex_unlock (&h->lock);
  return (0);
}