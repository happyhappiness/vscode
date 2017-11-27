static int wr_write (const data_set_t *ds, /* {{{ */
    const value_list_t *vl,
    user_data_t *ud)
{
  wr_node_t *node = ud->data;
  char ident[512];
  char key[512];
  char value[512];
  size_t value_size;
  char *value_ptr;
  int status;
  int i;

  status = FORMAT_VL (ident, sizeof (ident), vl);
  if (status != 0)
    return (status);
  ssnprintf (key, sizeof (key), "collectd/%s", ident);

  memset (value, 0, sizeof (value));
  value_size = sizeof (value);
  value_ptr = &value[0];

#define APPEND(...) do {                                             \
  status = snprintf (value_ptr, value_size, __VA_ARGS__);            \
  if (((size_t) status) > value_size)                                \
  {                                                                  \
    value_ptr += value_size;                                         \
    value_size = 0;                                                  \
  }                                                                  \
  else                                                               \
  {                                                                  \
    value_ptr += status;                                             \
    value_size -= status;                                            \
  }                                                                  \
} while (0)

  APPEND ("%lu", (unsigned long) vl->time);
  for (i = 0; i < ds->ds_num; i++)
  {
    if (ds->ds[i].type == DS_TYPE_COUNTER)
      APPEND ("%llu", vl->values[i].counter);
    else if (ds->ds[i].type == DS_TYPE_GAUGE)
      APPEND ("%g", vl->values[i].gauge);
    else if (ds->ds[i].type == DS_TYPE_DERIVE)
      APPEND ("%"PRIi64, vl->values[i].derive);
    else if (ds->ds[i].type == DS_TYPE_ABSOLUTE)
      APPEND ("%"PRIu64, vl->values[i].absolute);
    else
      assert (23 == 42);
  }

#undef APPEND

  pthread_mutex_lock (&node->lock);

  if (node->conn == NULL)
  {
    node->conn = credis_connect (node->host, node->port, node->timeout);
    if (node->conn == NULL)
    {
      ERROR ("write_redis plugin: Connecting to host \"%s\" (port %i) failed.",
          (node->host != NULL) ? node->host : "localhost",
          (node->port != 0) ? node->port : 6379);
      pthread_mutex_unlock (&node->lock);
      return (-1);
    }
  }

  /* "credis_zadd" doesn't handle a NULL pointer gracefully, so I'd rather
   * have a meaningful assertion message than a normal segmentation fault. */
  assert (node->conn != NULL);
  status = credis_zadd (node->conn, key, (double) vl->time, value);

  credis_sadd (node->conn, "collectd/values", ident);

  pthread_mutex_unlock (&node->lock);

  return (0);
}