static void free_host_config(host_config_t *hc) /* {{{ */
{
  host_config_t *next;

  if (hc == NULL)
    return;

  next = hc->next;

  sfree(hc->name);
  sfree(hc->host);
  sfree(hc->username);
  sfree(hc->password);
  sfree(hc->vfiler);

  free_cfg_disk(hc->cfg_disk);
  free_cfg_wafl(hc->cfg_wafl);
  free_cfg_volume_perf(hc->cfg_volume_perf);
  free_cfg_volume_usage(hc->cfg_volume_usage);
  free_cfg_quota(hc->cfg_quota);
  free_cfg_snapvault(hc->cfg_snapvault);
  free_cfg_system(hc->cfg_system);

  if (hc->srv != NULL)
    na_server_close(hc->srv);

  sfree(hc);

  free_host_config(next);
}