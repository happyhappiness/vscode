static void service_process_request (Pinba__Request *request) /* {{{ */
{
  pthread_mutex_lock (&stat_nodes_lock);

  for (unsigned int i = 0; i < stat_nodes_num; i++)
  {
    if ((stat_nodes[i].host != NULL)
        && (strcmp (request->hostname, stat_nodes[i].host) != 0))
      continue;

    if ((stat_nodes[i].server != NULL)
      && (strcmp (request->server_name, stat_nodes[i].server) != 0))
      continue;

    if ((stat_nodes[i].script != NULL)
      && (strcmp (request->script_name, stat_nodes[i].script) != 0))
      continue;

    service_statnode_process(&stat_nodes[i], request);
  }

  pthread_mutex_unlock(&stat_nodes_lock);
}