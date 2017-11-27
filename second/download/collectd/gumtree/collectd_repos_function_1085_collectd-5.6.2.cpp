static void free_cfg_snapvault(cfg_snapvault_t *sv) /* {{{ */
{
  if (sv == NULL)
    return;

  if (sv->query != NULL)
    na_elem_free(sv->query);

  sfree(sv);
}