int meta_data_as_string(meta_data_t *md, /* {{{ */
                        const char *key, char **value) {
  meta_entry_t *e;
  const char *actual;
  char buffer[MD_MAX_NONSTRING_CHARS]; /* For non-string types. */
  char *temp;
  int type;

  if ((md == NULL) || (key == NULL) || (value == NULL))
    return -EINVAL;

  pthread_mutex_lock(&md->lock);

  e = md_entry_lookup(md, key);
  if (e == NULL) {
    pthread_mutex_unlock(&md->lock);
    return -ENOENT;
  }

  type = e->type;

  switch (type) {
  case MD_TYPE_STRING:
    actual = e->value.mv_string;
    break;
  case MD_TYPE_SIGNED_INT:
    snprintf(buffer, sizeof(buffer), "%" PRIi64, e->value.mv_signed_int);
    actual = buffer;
    break;
  case MD_TYPE_UNSIGNED_INT:
    snprintf(buffer, sizeof(buffer), "%" PRIu64, e->value.mv_unsigned_int);
    actual = buffer;
    break;
  case MD_TYPE_DOUBLE:
    snprintf(buffer, sizeof(buffer), GAUGE_FORMAT, e->value.mv_double);
    actual = buffer;
    break;
  case MD_TYPE_BOOLEAN:
    actual = e->value.mv_boolean ? "true" : "false";
    break;
  default:
    pthread_mutex_unlock(&md->lock);
    ERROR("meta_data_as_string: unknown type %d for key `%s'", type, key);
    return -ENOENT;
  }

  pthread_mutex_unlock(&md->lock);

  temp = md_strdup(actual);
  if (temp == NULL) {
    ERROR("meta_data_as_string: md_strdup failed for key `%s'.", key);
    return -ENOMEM;
  }

  *value = temp;

  return 0;
}