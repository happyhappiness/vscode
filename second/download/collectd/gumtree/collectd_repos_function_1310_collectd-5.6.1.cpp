static unsigned int service_statnode_collect (pinba_statnode_t *res, /* {{{ */
    unsigned int index)
{
  pinba_statnode_t *node;

  if (stat_nodes_num == 0)
    return 0;

  /* begin collecting */
  if (index == 0)
    pthread_mutex_lock (&stat_nodes_lock);

  /* end collecting */
  if (index >= stat_nodes_num)
  {
    pthread_mutex_unlock (&stat_nodes_lock);
    return 0;
  }

  node = stat_nodes + index;
  memcpy (res, node, sizeof (*res));

  /* reset node */
  node->mem_peak = NAN;

  return (index + 1);
}