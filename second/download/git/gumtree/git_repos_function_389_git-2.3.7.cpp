static int lookup_credential(const char *fn, struct credential *c)
{
	parse_credential_file(fn, c, print_entry, NULL);
	return c->username && c->password;
}