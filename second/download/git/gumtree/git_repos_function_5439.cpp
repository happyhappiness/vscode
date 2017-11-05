static int reset_refs(const char *rev, const unsigned char *sha1)
{
	int update_ref_status;
	struct strbuf msg = STRBUF_INIT;
	unsigned char *orig = NULL, sha1_orig[20],
		*old_orig = NULL, sha1_old_orig[20];

	if (!get_sha1("ORIG_HEAD", sha1_old_orig))
		old_orig = sha1_old_orig;
	if (!get_sha1("HEAD", sha1_orig)) {
		orig = sha1_orig;
		set_reflog_message(&msg, "updating ORIG_HEAD", NULL);
		update_ref(msg.buf, "ORIG_HEAD", orig, old_orig, 0,
			   UPDATE_REFS_MSG_ON_ERR);
	} else if (old_orig)
		delete_ref("ORIG_HEAD", old_orig, 0);
	set_reflog_message(&msg, "updating HEAD", rev);
	update_ref_status = update_ref(msg.buf, "HEAD", sha1, orig, 0,
				       UPDATE_REFS_MSG_ON_ERR);
	strbuf_release(&msg);
	return update_ref_status;
}