static void host_free (void *void_host) /* {{{ */
{
  mb_host_t *host = void_host;

  if (host == NULL)
    return;

  slaves_free_all (host->slaves, host->slaves_num);
  sfree (host);
}