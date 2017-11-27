int plugin_notification_meta_copy(notification_t *dst,
                                  const notification_t *src) {
  assert(dst != NULL);
  assert(src != NULL);
  assert(dst != src);
  assert((src->meta == NULL) || (src->meta != dst->meta));

  for (notification_meta_t *meta = src->meta; meta != NULL; meta = meta->next) {
    if (meta->type == NM_TYPE_STRING)
      plugin_notification_meta_add_string(dst, meta->name,
                                          meta->nm_value.nm_string);
    else if (meta->type == NM_TYPE_SIGNED_INT)
      plugin_notification_meta_add_signed_int(dst, meta->name,
                                              meta->nm_value.nm_signed_int);
    else if (meta->type == NM_TYPE_UNSIGNED_INT)
      plugin_notification_meta_add_unsigned_int(dst, meta->name,
                                                meta->nm_value.nm_unsigned_int);
    else if (meta->type == NM_TYPE_DOUBLE)
      plugin_notification_meta_add_double(dst, meta->name,
                                          meta->nm_value.nm_double);
    else if (meta->type == NM_TYPE_BOOLEAN)
      plugin_notification_meta_add_boolean(dst, meta->name,
                                           meta->nm_value.nm_boolean);
  }

  return 0;
}