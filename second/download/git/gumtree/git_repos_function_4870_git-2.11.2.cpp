static const char *unique_tracking_name(const char *name, struct object_id *oid)
{
	struct tracking_name_data cb_data = { NULL, NULL, NULL, 1 };
	char src_ref[PATH_MAX];
	snprintf(src_ref, PATH_MAX, "refs/heads/%s", name);
	cb_data.src_ref = src_ref;
	cb_data.dst_oid = oid;
	for_each_remote(check_tracking_name, &cb_data);
	if (cb_data.unique)
		return cb_data.dst_ref;
	free(cb_data.dst_ref);
	return NULL;
}