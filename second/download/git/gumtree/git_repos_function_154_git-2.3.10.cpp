static int upload_pack_config(const char *var, const char *value, void *unused)
{
	if (!strcmp("uploadpack.allowtipsha1inwant", var))
		allow_tip_sha1_in_want = git_config_bool(var, value);
	else if (!strcmp("uploadpack.keepalive", var)) {
		keepalive = git_config_int(var, value);
		if (!keepalive)
			keepalive = -1;
	}
	return parse_hide_refs_config(var, value, "uploadpack");
}