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