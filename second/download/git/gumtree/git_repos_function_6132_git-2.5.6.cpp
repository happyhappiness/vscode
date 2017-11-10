static char *keyring_object(struct credential *c)
{
	if (!c->path)
		return NULL;

	if (c->port)
		return g_strdup_printf("%s:%hd/%s", c->host, c->port, c->path);

	return g_strdup_printf("%s/%s", c->host, c->path);
}