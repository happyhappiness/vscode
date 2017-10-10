	if (walker->get_verbosely)
		fprintf(stderr, fmt, hex);
}

static void report_missing(const struct object *obj)
{
	fprintf(stderr, "Cannot obtain needed %s %s\n",
		obj->type ? typename(obj->type): "object",
		oid_to_hex(&obj->oid));
	if (!is_null_sha1(current_commit_sha1))
		fprintf(stderr, "while processing commit %s.\n",
			sha1_to_hex(current_commit_sha1));
}

static int process(struct walker *walker, struct object *obj);
