static void sensu_close_socket(struct sensu_host *host) /* {{{ */
{
  if (host->s != -1)
    close(host->s);
  host->s = -1;

}