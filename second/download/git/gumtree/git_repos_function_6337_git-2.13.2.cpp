static int rename_tmp_log(struct files_ref_store *refs, const char *newrefname)
{
	struct strbuf path = STRBUF_INIT;
	struct strbuf tmp = STRBUF_INIT;
	struct rename_cb cb;
	int ret;

	files_reflog_path(refs, &path, newrefname);
	files_reflog_path(refs, &tmp, TMP_RENAMED_LOG);
	cb.tmp_renamed_log = tmp.buf;
	ret = raceproof_create_file(path.buf, rename_tmp_log_callback, &cb);
	if (ret) {
		if (errno == EISDIR)
			error("directory not empty: %s", path.buf);
		else
			error("unable to move logfile %s to %s: %s",
			      tmp.buf, path.buf,
			      strerror(cb.true_errno));
	}

	strbuf_release(&path);
	strbuf_release(&tmp);
	return ret;
}