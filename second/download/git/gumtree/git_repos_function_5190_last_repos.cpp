static const char *unique_tracking_name(const char *name, struct object_id *oid)
{
	struct tracking_name_data cb_data = { NULL, NULL, NULL, 1 };
	cb_data.src_ref = xstrfmt("refs/heads/%s", name);
	cb_data.dst_oid = oid;
	for_each_remote(check_tracking_name, &cb_data);
	free(cb_data.src_ref);
	if (cb_data.unique)
		return cb_data.dst_ref;
	free(cb_data.dst_ref);
	return NULL;
}