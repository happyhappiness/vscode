		die("git fetch-pack: fetch failed.");

 all_done:
	return ref;
}

static int fetch_pack_config(const char *var, const char *value, void *cb)
{
	if (strcmp(var, "fetch.unpacklimit") == 0) {
		fetch_unpack_limit = git_config_int(var, value);
		return 0;
	}

	if (strcmp(var, "transfer.unpacklimit") == 0) {
		transfer_unpack_limit = git_config_int(var, value);
		return 0;
	}

	if (strcmp(var, "repack.usedeltabaseoffset") == 0) {
		prefer_ofs_delta = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "fetch.fsckobjects")) {
		fetch_fsck_objects = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "transfer.fsckobjects")) {
		transfer_fsck_objects = git_config_bool(var, value);
		return 0;
	}

	return git_default_config(var, value, cb);
}

static void fetch_pack_setup(void)
{
	static int did_setup;
	if (did_setup)
		return;
	git_config(fetch_pack_config, NULL);
	if (0 <= transfer_unpack_limit)
		unpack_limit = transfer_unpack_limit;
	else if (0 <= fetch_unpack_limit)
		unpack_limit = fetch_unpack_limit;
	did_setup = 1;
}
