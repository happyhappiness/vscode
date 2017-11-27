int plugin_notification_meta_free (notification_meta_t *n)
{
  notification_meta_t *this;
  notification_meta_t *next;

  if (n == NULL)
  {
    ERROR ("plugin_notification_meta_free: n == NULL!");
    return (-1);
  }

  this = n;
  while (this != NULL)
  {
    next = this->next;

    if (this->type == NM_TYPE_STRING)
    {
      /* Assign to a temporary variable to work around nm_string's const
       * modifier. */
      void *tmp = (void *) this->nm_value.nm_string;

      sfree (tmp);
      this->nm_value.nm_string = NULL;
    }
    sfree (this);

    this = next;
  }

  return (0);
}