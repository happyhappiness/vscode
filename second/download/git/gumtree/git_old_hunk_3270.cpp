		struct credential_cache_entry *e = lookup_credential(&c);
		if (e) {
			fprintf(out, "username=%s\n", e->item.username);
			fprintf(out, "password=%s\n", e->item.password);
		}
	}
	else if (!strcmp(action.buf, "exit"))
		exit(0);
	else if (!strcmp(action.buf, "erase"))
		remove_credential(&c);
	else if (!strcmp(action.buf, "store")) {
		if (timeout < 0)
			warning("cache client didn't specify a timeout");
		else if (!c.username || !c.password)
