static void
mutt_hcache_dbt_init(DBT * dbt, void *data, size_t len)
{
  dbt->data = data;
  dbt->size = dbt->ulen = len;
  dbt->dlen = dbt->doff = 0;
  dbt->flags = DB_DBT_USERMEM;
}