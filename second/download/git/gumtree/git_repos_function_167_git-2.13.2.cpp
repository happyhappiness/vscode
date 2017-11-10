static int upload_pack_config(const char *var, const char *value, void *unused)
{
	if (!strcmp("uploadpack.allowtipsha1inwant", var)) {
		if (git_config_bool(var, value))
			allow_unadvertised_object_request |= ALLOW_TIP_SHA1;
		else
			allow_unadvertised_object_request &= ~ALLOW_TIP_SHA1;
	} else if (!strcmp("uploadpack.allowreachablesha1inwant", var)) {
		if (git_config_bool(var, value))
			allow_unadvertised_object_request |= ALLOW_REACHABLE_SHA1;
		else
			allow_unadvertised_object_request &= ~ALLOW_REACHABLE_SHA1;
	} else if (!strcmp("uploadpack.allowanysha1inwant", var)) {
		if (git_config_bool(var, value))
			allow_unadvertised_object_request |= ALLOW_ANY_SHA1;
		else
			allow_unadvertised_object_request &= ~ALLOW_ANY_SHA1;
	} else if (!strcmp("uploadpack.keepalive", var)) {
		keepalive = git_config_int(var, value);
		if (!keepalive)
			keepalive = -1;
	} else if (current_config_scope() != CONFIG_SCOPE_REPO) {
		if (!strcmp("uploadpack.packobjectshook", var))
			return git_config_string(&pack_objects_hook, var, value);
	}
	return parse_hide_refs_config(var, value, "uploadpack");
}