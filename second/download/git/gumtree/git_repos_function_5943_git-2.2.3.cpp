static void credential_clear(struct credential *c)
{
	g_free(c->protocol);
	g_free(c->host);
	g_free(c->path);
	g_free(c->username);
	gnome_keyring_memory_free(c->password);

	credential_init(c);
}