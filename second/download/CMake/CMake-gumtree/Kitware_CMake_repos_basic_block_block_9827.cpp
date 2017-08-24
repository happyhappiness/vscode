{
		st = tree_current_stat(t);
		if (st == NULL)
			return (0);
		if (!S_ISDIR(st->st_mode))
			return (0);
	}