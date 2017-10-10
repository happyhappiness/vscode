		       head->tree->object.oid.hash,
		       "", &opts);
	diffcore_std(&opts);
	diff_flush(&opts);

	fprintf(rev->diffopt.file, "\n");
	print_signature(rev->diffopt.file);
}

static const char *clean_message_id(const char *msg_id)
{
	char ch;
	const char *a, *z, *m;
