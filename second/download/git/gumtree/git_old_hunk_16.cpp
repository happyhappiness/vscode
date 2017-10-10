	unsigned char junk[20];

	if (!(flags & REF_ISSYMREF))
		return 0;

	resolves_to = resolve_ref_unsafe(refname, junk, 0, NULL);
	if (!resolves_to || strcmp(resolves_to, d->refname))
		return 0;

	fprintf(d->fp, d->msg_fmt, refname);
	fputc('\n', d->fp);
	return 0;
}

void warn_dangling_symref(FILE *fp, const char *msg_fmt, const char *refname)
{
	struct warn_if_dangling_data data;

	data.fp = fp;
	data.refname = refname;
	data.msg_fmt = msg_fmt;
	for_each_rawref(warn_if_dangling_symref, &data);
}

/*
 * Call fn for each reference in the specified ref_cache, omitting
