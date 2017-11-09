void credential_reject(struct credential *c)
{
	int i;

	credential_apply_config(c);

	for (i = 0; i < c->helpers.nr; i++)
		credential_do(c, c->helpers.items[i].string, "erase");

	FREE_AND_NULL(c->username);
	FREE_AND_NULL(c->password);
	c->approved = 0;
}