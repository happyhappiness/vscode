	}
	return 0;
}

static int remove_branches(struct string_list *branches)
{
	int i, result = 0;
	for (i = 0; i < branches->nr; i++) {
		struct string_list_item *item = branches->items + i;
		const char *refname = item->string;
		unsigned char *sha1 = item->util;

		if (delete_ref(refname, sha1, 0))
			result |= error(_("Could not remove branch %s"), refname);
	}
	return result;
}

static int rm(int argc, const char **argv)
{
	struct option options[] = {
