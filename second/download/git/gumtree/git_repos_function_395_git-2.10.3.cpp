void credential_reject(struct credential *c)
{
	int i;

	credential_apply_config(c);

	for (i = 0; i < c->helpers.nr; i++)
		credential_do(c, c->helpers.items[i].string, "erase");

	free(c->username);
	c->username = NULL;
	free(c->password);
	c->password = NULL;
	c->approved = 0;
}