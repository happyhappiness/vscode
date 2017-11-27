static int data_copy(mb_data_t **dst, const mb_data_t *src) /* {{{ */
{
  mb_data_t *tmp;
  int status;

  if ((dst == NULL) || (src == NULL))
    return EINVAL;

  tmp = malloc(sizeof(*tmp));
  if (tmp == NULL)
    return ENOMEM;
  memcpy(tmp, src, sizeof(*tmp));
  tmp->name = NULL;
  tmp->next = NULL;

  tmp->name = strdup(src->name);
  if (tmp->name == NULL) {
    sfree(tmp);
    return ENOMEM;
  }

  status = data_append(dst, tmp);
  if (status != 0) {
    sfree(tmp->name);
    sfree(tmp);
    return status;
  }

  return 0;
}