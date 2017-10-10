		len = strlen(item->string);
		if (!refname[len] || refname[len] == '/')
			return 1;
	}
	return 0;
}
