static int data_copy_by_name(mb_data_t **dst, mb_data_t *src, /* {{{ */
                             const char *name) {
  mb_data_t *ptr;

  if ((dst == NULL) || (src == NULL) || (name == NULL))
    return EINVAL;

  ptr = data_get_by_name(src, name);
  if (ptr == NULL)
    return ENOENT;

  return data_copy(dst, ptr);
}