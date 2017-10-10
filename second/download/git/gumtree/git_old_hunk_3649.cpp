	struct strbuf out = STRBUF_INIT;
	struct pretty_print_context pp = {0};

	pp.fmt = rev->commit_format;
	pp.date_mode = rev->date_mode;
	pp_user_info(&pp, "Tagger", &out, buf, get_log_output_encoding());
	printf("%s", out.buf);
	strbuf_release(&out);
}

static int show_blob_object(const unsigned char *sha1, struct rev_info *rev, const char *obj_name)
{
	unsigned char sha1c[20];
	struct object_context obj_context;
	char *buf;
	unsigned long size;

	fflush(stdout);
	if (!DIFF_OPT_TOUCHED(&rev->diffopt, ALLOW_TEXTCONV) ||
	    !DIFF_OPT_TST(&rev->diffopt, ALLOW_TEXTCONV))
		return stream_blob_to_fd(1, sha1, NULL, 0);

	if (get_sha1_with_context(obj_name, 0, sha1c, &obj_context))
		die(_("Not a valid object name %s"), obj_name);
