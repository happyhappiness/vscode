static void free_cfg_wafl(cfg_wafl_t *cw) /* {{{ */
{
  if (cw == NULL)
    return;

  if (cw->query != NULL)
    na_elem_free(cw->query);

  sfree(cw);
}