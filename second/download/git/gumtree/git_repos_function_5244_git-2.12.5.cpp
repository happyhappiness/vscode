static int fsck_handle_reflog(const char *logname, const struct object_id *oid,
			      int flag, void *cb_data)
{
	for_each_reflog_ent(logname, fsck_handle_reflog_ent, (void *)logname);
	return 0;
}