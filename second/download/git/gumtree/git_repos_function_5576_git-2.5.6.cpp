static void end_revision(const char *note_ref)
{
	struct strbuf mark = STRBUF_INIT;
	if (rev_ctx.revision) {
		fast_export_end_commit(rev_ctx.revision);
		fast_export_begin_note(rev_ctx.revision, "remote-svn",
				"Note created by remote-svn.", rev_ctx.timestamp, note_ref);
		strbuf_addf(&mark, ":%"PRIu32, rev_ctx.revision);
		fast_export_note(mark.buf, "inline");
		fast_export_buf_to_data(&rev_ctx.note);
	}
}