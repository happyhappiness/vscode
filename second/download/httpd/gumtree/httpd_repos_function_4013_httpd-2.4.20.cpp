static void env2env(apr_table_t *table, const char *name)
{
    add_unless_null(table, name, getenv(name));
}