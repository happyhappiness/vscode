void credential_clear(struct credential *c)
{
	free(c->protocol);
	free(c->host);
	free(c->path);
	free(c->username);
	free(c->password);
	string_list_clear(&c->helpers, 0);

	credential_init(c);
}