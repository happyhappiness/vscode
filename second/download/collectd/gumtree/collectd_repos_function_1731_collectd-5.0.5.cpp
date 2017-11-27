static int plugin_notification_meta_add (notification_t *n,
    const char *name,
    enum notification_meta_type_e type,
    const void *value)
{
  notification_meta_t *meta;
  notification_meta_t *tail;

  if ((n == NULL) || (name == NULL) || (value == NULL))
  {
    ERROR ("plugin_notification_meta_add: A pointer is NULL!");
    return (-1);
  }

  meta = (notification_meta_t *) malloc (sizeof (notification_meta_t));
  if (meta == NULL)
  {
    ERROR ("plugin_notification_meta_add: malloc failed.");
    return (-1);
  }
  memset (meta, 0, sizeof (notification_meta_t));

  sstrncpy (meta->name, name, sizeof (meta->name));
  meta->type = type;

  switch (type)
  {
    case NM_TYPE_STRING:
    {
      meta->nm_value.nm_string = strdup ((const char *) value);
      if (meta->nm_value.nm_string == NULL)
      {
        ERROR ("plugin_notification_meta_add: strdup failed.");
        sfree (meta);
        return (-1);
      }
      break;
    }
    case NM_TYPE_SIGNED_INT:
    {
      meta->nm_value.nm_signed_int = *((int64_t *) value);
      break;
    }
    case NM_TYPE_UNSIGNED_INT:
    {
      meta->nm_value.nm_unsigned_int = *((uint64_t *) value);
      break;
    }
    case NM_TYPE_DOUBLE:
    {
      meta->nm_value.nm_double = *((double *) value);
      break;
    }
    case NM_TYPE_BOOLEAN:
    {
      meta->nm_value.nm_boolean = *((_Bool *) value);
      break;
    }
    default:
    {
      ERROR ("plugin_notification_meta_add: Unknown type: %i", type);
      sfree (meta);
      return (-1);
    }
  } /* switch (type) */

  meta->next = NULL;
  tail = n->meta;
  while ((tail != NULL) && (tail->next != NULL))
    tail = tail->next;

  if (tail == NULL)
    n->meta = meta;
  else
    tail->next = meta;

  return (0);
}