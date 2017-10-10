	for (i = 0; i < array.nr; i++)
		format_and_print_ref_item(array.items[i], maxwidth, filter, remote_prefix);

	ref_array_clear(&array);
}

static void rename_branch(const char *oldname, const char *newname, int force)
{
	struct strbuf oldref = STRBUF_INIT, newref = STRBUF_INIT, logmsg = STRBUF_INIT;
	struct strbuf oldsection = STRBUF_INIT, newsection = STRBUF_INIT;
	int recovery = 0;
	int clobber_head_ok;
