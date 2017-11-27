static void reheap (c_heap_t *h, size_t root, enum reheap_direction dir)
{
  size_t left;
  size_t right;
  size_t min;
  int status;

  /* Calculate the positions of the children */
  left = (2 * root) + 1;
  if (left >= h->list_len)
    left = 0;

  right = (2 * root) + 2;
  if (right >= h->list_len)
    right = 0;

  /* Check which one of the children is smaller. */
  if ((left == 0) && (right == 0))
    return;
  else if (left == 0)
    min = right;
  else if (right == 0)
    min = left;
  else
  {
    status = h->compare (h->list[left], h->list[right]);
    if (status > 0)
      min = right;
    else
      min = left;
  }

  status = h->compare (h->list[root], h->list[min]);
  if (status <= 0)
  {
    /* We didn't need to change anything, so the rest of the tree should be
     * okay now. */
    return;
  }
  else /* if (status > 0) */
  {
    void *tmp;

    tmp = h->list[root];
    h->list[root] = h->list[min];
    h->list[min] = tmp;
  }

  if ((dir == DIR_UP) && (root == 0))
    return;

  if (dir == DIR_UP)
    reheap (h, root / 2, dir);
  else if (dir == DIR_DOWN)
    reheap (h, min, dir);
}