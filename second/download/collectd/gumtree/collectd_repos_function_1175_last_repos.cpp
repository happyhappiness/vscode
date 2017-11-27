static host_config_t *cna_shallow_clone_host(host_config_t *host) /* {{{ */
{
  host_config_t *clone;

  if (host == NULL)
    return NULL;

  clone = cna_alloc_host();
  if (clone == NULL)
    return NULL;

  if (host->name != NULL) {
    clone->name = strdup(host->name);
    if (clone->name == NULL) {
      free_host_config(clone);
      return NULL;
    }
  }

  clone->protocol = host->protocol;

  if (host->host != NULL) {
    clone->host = strdup(host->host);
    if (clone->host == NULL) {
      free_host_config(clone);
      return NULL;
    }
  }

  clone->port = host->port;

  if (host->username != NULL) {
    clone->username = strdup(host->username);
    if (clone->username == NULL) {
      free_host_config(clone);
      return NULL;
    }
  }
  if (host->password != NULL) {
    clone->password = strdup(host->password);
    if (clone->password == NULL) {
      free_host_config(clone);
      return NULL;
    }
  }

  clone->interval = host->interval;

  return clone;
}