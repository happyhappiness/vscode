void credential_init(struct credential *c)
{
	memset(c, 0, sizeof(*c));
	c->helpers.strdup_strings = 1;
}