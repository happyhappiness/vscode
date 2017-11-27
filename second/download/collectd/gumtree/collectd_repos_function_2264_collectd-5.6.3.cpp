lcc_network_buffer_t *lcc_network_buffer_create(size_t size) /* {{{ */
{
  lcc_network_buffer_t *nb;

  if (size == 0)
    size = LCC_NETWORK_BUFFER_SIZE_DEFAULT;

  if (size < 128) {
    errno = EINVAL;
    return (NULL);
  }

  nb = calloc(1, sizeof(*nb));
  if (nb == NULL)
    return (NULL);

  nb->size = size;
  nb->buffer = calloc(1, nb->size);
  if (nb->buffer == NULL) {
    free(nb);
    return (NULL);
  }

  nb->ptr = nb->buffer;
  nb->free = nb->size;

  nb->seclevel = NONE;
  nb->username = NULL;
  nb->password = NULL;

  return (nb);
}