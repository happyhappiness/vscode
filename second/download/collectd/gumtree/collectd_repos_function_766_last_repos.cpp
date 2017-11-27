static int redis_init(void) /* {{{ */
{
  redis_node_t rn = {.name = "default",
                     .host = REDIS_DEF_HOST,
                     .port = REDIS_DEF_PORT,
                     .timeout.tv_sec = 0,
                     .timeout.tv_usec = REDIS_DEF_TIMEOUT,
                     .next = NULL};

  if (nodes_head == NULL)
    redis_node_add(&rn);

  return 0;
}