static void mv_free_match (mv_match_t *m) /* {{{ */
{
  int i;
  
  if (m == NULL)
    return;

  if (m->data_sources != NULL)
  {
    for (i = 0; i < m->data_sources_num; ++i)
      free(m->data_sources[i]);
    free(m->data_sources);
  }
  
  free (m);
}