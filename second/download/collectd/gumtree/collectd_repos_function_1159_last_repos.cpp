static int cna_setup_system(cfg_system_t *cs) /* {{{ */
{
  if (cs == NULL)
    return EINVAL;

  if (cs->query != NULL)
    return 0;

  cs->query = na_elem_new("perf-object-get-instances");
  if (cs->query == NULL) {
    ERROR("netapp plugin: na_elem_new failed.");
    return -1;
  }
  na_child_add_string(cs->query, "objectname", "system");

  return 0;
}