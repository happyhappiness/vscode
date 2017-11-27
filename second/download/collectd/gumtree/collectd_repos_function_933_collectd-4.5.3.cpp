int plugin_notification_meta_free (notification_t *n)
{
  notification_meta_t *this;
  notification_meta_t *next;

  if (n == NULL)
  {
    ERROR ("plugin_notification_meta_free: n == NULL!");
    return (-1);
  }

  this = n->meta;
  n->meta = NULL;
  while (this != NULL)
  {
    next = this->next;

    if (this->type == NM_TYPE_STRING)
    {
      free ((char *)this->nm_value.nm_string);
      this->nm_value.nm_string = NULL;
    }
    sfree (this);

    this = next;
  }

  return (0);
}