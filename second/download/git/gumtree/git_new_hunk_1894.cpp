
	fprintf(out, "%s ", sha1_to_hex(obj->sha1));
	show_path_truncated(out, &leaf);
	fputc('\n', out);
}

static void mark_blob_uninteresting(struct blob *blob)
{
	if (!blob)
		return;
	if (blob->object.flags & UNINTERESTING)
		return;
