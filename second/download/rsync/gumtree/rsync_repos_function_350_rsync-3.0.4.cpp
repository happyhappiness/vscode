char *full_fname(const char *fn)
{
	static char *result = NULL;
	char *m1, *m2, *m3;
	char *p1, *p2;

	if (result)
		free(result);

	if (*fn == '/')
		p1 = p2 = "";
	else {
		p1 = curr_dir + module_dirlen;
		for (p2 = p1; *p2 == '/'; p2++) {}
		if (*p2)
			p2 = "/";
	}
	if (module_id >= 0) {
		m1 = " (in ";
		m2 = lp_name(module_id);
		m3 = ")";
	} else
		m1 = m2 = m3 = "";

	if (asprintf(&result, "\"%s%s%s\"%s%s%s", p1, p2, fn, m1, m2, m3) <= 0)
		out_of_memory("full_fname");

	return result;
}