void warn_dangling_symrefs(FILE *fp, const char *msg_fmt, const struct string_list *refnames)
{
	struct warn_if_dangling_data data;

	data.fp = fp;
	data.refname = NULL;
	data.refnames = refnames;
	data.msg_fmt = msg_fmt;
	for_each_rawref(warn_if_dangling_symref, &data);
}