static int redis_init (void) /* {{{ */
{
  redis_node_t rn = { "default", REDIS_DEF_HOST, REDIS_DEF_PORT,
    REDIS_DEF_TIMEOUT, /* next = */ NULL };

  if (nodes_head == NULL)
    redis_node_add (&rn);

  return (0);
}