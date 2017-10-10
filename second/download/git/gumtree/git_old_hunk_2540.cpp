	strbuf_release(&msg);
	ret = merge_abort(o);
	free(local_ref_to_free);
	return ret;
}

static int merge(int argc, const char **argv, const char *prefix)
{
	struct strbuf remote_ref = STRBUF_INIT, msg = STRBUF_INIT;
	unsigned char result_sha1[20];
	struct notes_tree *t;
	struct notes_merge_options o;
