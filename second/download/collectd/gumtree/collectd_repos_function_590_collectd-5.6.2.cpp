static void sensu_free(void *p) /* {{{ */
{
  struct sensu_host *host = p;

  if (host == NULL)
    return;

  pthread_mutex_lock(&host->lock);

  host->reference_count--;
  if (host->reference_count > 0) {
    pthread_mutex_unlock(&host->lock);
    return;
  }

  sensu_close_socket(host);
  if (host->res != NULL) {
    freeaddrinfo(host->res);
    host->res = NULL;
  }
  sfree(host->service);
  sfree(host->event_service_prefix);
  sfree(host->name);
  sfree(host->node);
  sfree(host->separator);
  free_str_list(&(host->metric_handlers));
  free_str_list(&(host->notification_handlers));
  pthread_mutex_destroy(&host->lock);
  sfree(host);
}