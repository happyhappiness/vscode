void add_exclude(struct exclude_struct ***listp, const char *pattern, int include)
{
	struct exclude_struct **list = *listp;
	int len = 0;

	if (*pattern == '!' && !pattern[1]) {
	    free_exclude_list(listp);
	    return;
	}

	if (list)
		for (; list[len]; len++) {}

 	list = *listp = realloc_array(list, struct exclude_struct *, len+2);

	if (!list || !(list[len] = make_exclude(pattern, include)))
		out_of_memory("add_exclude");

	if (verbose > 2) {
		rprintf(FINFO,"add_exclude(%s,%s)\n",pattern,
			include ? "include" : "exclude");
	}

	list[len+1] = NULL;
}