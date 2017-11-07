static void
mutt_hcache_dbt_empty_init(DBT * dbt)
{
  dbt->data = NULL;
  dbt->size = dbt->ulen = dbt->dlen = dbt->doff = 0;
  dbt->flags = 0;
}