static int cna_setup_snapvault(cfg_snapvault_t *sv) /* {{{ */
{
  if (sv == NULL)
    return EINVAL;

  if (sv->query != NULL)
    return 0;

  sv->query =
      na_elem_new("snapvault-secondary-relationship-status-list-iter-start");
  if (sv->query == NULL) {
    ERROR("netapp plugin: na_elem_new failed.");
    return -1;
  }

  return 0;
}