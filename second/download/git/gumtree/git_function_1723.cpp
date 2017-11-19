void credential_fill(struct credential *c)
{
	int i;

	if (c->username && c->password)
		return;

	credential_apply_config(c);

	for (i = 0; i < c->helpers.nr; i++) {
		credential_do(c, c->helpers.items[i].string, "get");
		if (c->username && c->password)
			return;
		if (c->quit)
			die("credential helper '%s' told us to quit",
			    c->helpers.items[i].string);
	}

	credential_getpass(c);
	if (!c->username && !c->password)
		die("unable to get password from user");
}