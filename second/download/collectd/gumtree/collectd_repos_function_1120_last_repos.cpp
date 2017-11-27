static void free_cfg_system(cfg_system_t *cs) /* {{{ */
{
  if (cs == NULL)
    return;

  if (cs->query != NULL)
    na_elem_free(cs->query);

  sfree(cs);
}