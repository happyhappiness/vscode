static void make_identity_table(apr_xlate_t *convset)
{
  int i;

  convset->sbcs_table = apr_palloc(convset->pool, 256);
  for (i = 0; i < 256; i++)
      convset->sbcs_table[i] = i;
}