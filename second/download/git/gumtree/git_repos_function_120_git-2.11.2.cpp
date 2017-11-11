void format_commit_message(const struct commit *commit,
			   const char *format, struct strbuf *sb,
			   const struct pretty_print_context *pretty_ctx)
{
	struct format_commit_context context;
	const char *output_enc = pretty_ctx->output_encoding;
	const char *utf8 = "UTF-8";

	memset(&context, 0, sizeof(context));
	context.commit = commit;
	context.pretty_ctx = pretty_ctx;
	context.wrap_start = sb->len;
	/*
	 * convert a commit message to UTF-8 first
	 * as far as 'format_commit_item' assumes it in UTF-8
	 */
	context.message = logmsg_reencode(commit,
					  &context.commit_encoding,
					  utf8);

	strbuf_expand(sb, format, format_commit_item, &context);
	rewrap_message_tail(sb, &context, 0, 0, 0);

	/* then convert a commit message to an actual output encoding */
	if (output_enc) {
		if (same_encoding(utf8, output_enc))
			output_enc = NULL;
	} else {
		if (context.commit_encoding &&
		    !same_encoding(context.commit_encoding, utf8))
			output_enc = context.commit_encoding;
	}

	if (output_enc) {
		int outsz;
		char *out = reencode_string_len(sb->buf, sb->len,
						output_enc, utf8, &outsz);
		if (out)
			strbuf_attach(sb, out, outsz, outsz + 1);
	}

	free(context.commit_encoding);
	unuse_commit_buffer(commit, context.message);
}