		if (*type_set) {
			if (!val)
				return;
			die("invalid dump: sets type twice");
		}
		if (!val) {
			node_ctx.type = S_IFREG | 0644;
			return;
		}
		*type_set = 1;
		node_ctx.type = keylen == strlen("svn:executable") ?
				(S_IFREG | 0755) :
				S_IFLNK;
	}
}

static void die_short_read(void)
{
	if (buffer_ferror(&input))
