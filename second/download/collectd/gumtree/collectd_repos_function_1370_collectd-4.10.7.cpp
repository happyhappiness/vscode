static int data_append (mb_data_t **dst, mb_data_t *src) /* {{{ */
{
  mb_data_t *ptr;

  if ((dst == NULL) || (src == NULL))
    return (EINVAL);

  ptr = *dst;

  if (ptr == NULL)
  {
    *dst = src;
    return (0);
  }

  while (ptr->next != NULL)
    ptr = ptr->next;

  ptr->next = src;

  return (0);
}