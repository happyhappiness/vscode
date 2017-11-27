static struct chain_head *iptcc_alloc_chain_head(const char *name, int hooknum)
{
	struct chain_head *c = malloc(sizeof(*c));
	if (!c)
		return NULL;
	memset(c, 0, sizeof(*c));

	strncpy(c->name, name, TABLE_MAXNAMELEN);
	c->hooknum = hooknum;
	INIT_LIST_HEAD(&c->rules);

	return c;
}