static int reset_refs(const char *rev, const struct object_id *oid)
{
	int update_ref_status;
	struct strbuf msg = STRBUF_INIT;
	struct object_id *orig = NULL, oid_orig,
		*old_orig = NULL, oid_old_orig;

	if (!get_oid("ORIG_HEAD", &oid_old_orig))
		old_orig = &oid_old_orig;
	if (!get_oid("HEAD", &oid_orig)) {
		orig = &oid_orig;
		set_reflog_message(&msg, "updating ORIG_HEAD", NULL);
		update_ref_oid(msg.buf, "ORIG_HEAD", orig, old_orig, 0,
			   UPDATE_REFS_MSG_ON_ERR);
	} else if (old_orig)
		delete_ref(NULL, "ORIG_HEAD", old_orig->hash, 0);
	set_reflog_message(&msg, "updating HEAD", rev);
	update_ref_status = update_ref_oid(msg.buf, "HEAD", oid, orig, 0,
				       UPDATE_REFS_MSG_ON_ERR);
	strbuf_release(&msg);
	return update_ref_status;
}