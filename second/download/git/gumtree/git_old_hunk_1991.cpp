	credential_apply_config(c);

	for (i = 0; i < c->helpers.nr; i++) {
		credential_do(c, c->helpers.items[i].string, "get");
		if (c->username && c->password)
			return;
	}

	credential_getpass(c);
	if (!c->username && !c->password)
		die("unable to get password from user");
}
