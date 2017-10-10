		hashcpy(ce->sha1, patch->threeway_stage[stage - 1].hash);
		if (add_cache_entry(ce, ADD_CACHE_OK_TO_ADD) < 0)
			die(_("unable to add cache entry for %s"), patch->new_name);
	}
}

static void create_file(struct patch *patch)
{
	char *path = patch->new_name;
	unsigned mode = patch->new_mode;
	unsigned long size = patch->resultsize;
	char *buf = patch->result;

	if (!mode)
		mode = S_IFREG | 0644;
	create_one_file(path, mode, buf, size);

	if (patch->conflicted_threeway)
		add_conflicted_stages_file(patch);
	else
		add_index_file(path, mode, buf, size);
}

/* phase zero is to remove, phase one is to create */
static void write_out_one_result(struct patch *patch, int phase)
{
	if (patch->is_delete > 0) {
		if (phase == 0)
			remove_file(patch, 1);
		return;
	}
	if (patch->is_new > 0 || patch->is_copy) {
		if (phase == 1)
			create_file(patch);
		return;
	}
	/*
	 * Rename or modification boils down to the same
	 * thing: remove the old, write the new
	 */
	if (phase == 0)
		remove_file(patch, patch->is_rename);
	if (phase == 1)
		create_file(patch);
}

static int write_out_one_reject(struct patch *patch)
{
	FILE *rej;
	char namebuf[PATH_MAX];
	struct fragment *frag;
	int cnt = 0;
	struct strbuf sb = STRBUF_INIT;
