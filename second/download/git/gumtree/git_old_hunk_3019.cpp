	return 0;
}

int open_pack_index(struct packed_git *p)
{
	char *idx_name;
	int ret;

	if (p->index_data)
		return 0;

	idx_name = xstrdup(p->pack_name);
	strcpy(idx_name + strlen(idx_name) - strlen(".pack"), ".idx");
	ret = check_packed_git_idx(idx_name, p);
	free(idx_name);
	return ret;
}

static void scan_windows(struct packed_git *p,
