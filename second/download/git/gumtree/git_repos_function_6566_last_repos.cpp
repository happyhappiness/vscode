static void begin_revision(const char *remote_ref)
{
	if (!rev_ctx.revision)	/* revision 0 gets no git commit. */
		return;
	fast_export_begin_commit(rev_ctx.revision, rev_ctx.author.buf,
		&rev_ctx.log, dump_ctx.uuid.buf, dump_ctx.url.buf,
		rev_ctx.timestamp, remote_ref);
}