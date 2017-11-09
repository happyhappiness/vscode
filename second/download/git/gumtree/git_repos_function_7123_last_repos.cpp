static char *make_label(struct credential *c)
{
	if (c->port)
		return g_strdup_printf("Git: %s://%s:%hu/%s",
					c->protocol, c->host, c->port, c->path ? c->path : "");
	else
		return g_strdup_printf("Git: %s://%s/%s",
					c->protocol, c->host, c->path ? c->path : "");
}