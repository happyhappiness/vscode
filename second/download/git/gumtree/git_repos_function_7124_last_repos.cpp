static GHashTable *make_attr_list(struct credential *c)
{
	GHashTable *al = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);

	if (c->username)
		g_hash_table_insert(al, "user", g_strdup(c->username));
	if (c->protocol)
		g_hash_table_insert(al, "protocol", g_strdup(c->protocol));
	if (c->host)
		g_hash_table_insert(al, "server", g_strdup(c->host));
	if (c->port)
		g_hash_table_insert(al, "port", g_strdup_printf("%hu", c->port));
	if (c->path)
		g_hash_table_insert(al, "object", g_strdup(c->path));

	return al;
}