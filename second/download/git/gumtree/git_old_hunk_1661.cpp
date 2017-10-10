		if (*type_set) {
			if (!val)
				return;
			die("invalid dump: sets type twice");
		}
		if (!val) {
			node_ctx.type = REPO_MODE_BLB;
			return;
		}
		*type_set = 1;
		node_ctx.type = keylen == strlen("svn:executable") ?
				REPO_MODE_EXE :
				REPO_MODE_LNK;
	}
}

static void die_short_read(void)
{
	if (buffer_ferror(&input))
