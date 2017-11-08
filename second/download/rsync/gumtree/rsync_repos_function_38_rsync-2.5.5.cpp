void add_exclude_list(const char *pattern, struct exclude_struct ***list, int include)
{
	int len=0;
	if (list && *list)
		for (; (*list)[len]; len++) ;

	if (strcmp(pattern,"!") == 0) {
		if (verbose > 2)
			rprintf(FINFO,"clearing exclude list\n");
		while ((len)--) {
			free_exclude((*list)[len]);
		}
		free((*list));
		*list = NULL;
		return;
	}

	*list = (struct exclude_struct **)Realloc(*list,sizeof(struct exclude_struct *)*(len+2));
	
	if (!*list || !((*list)[len] = make_exclude(pattern, include)))
		out_of_memory("add_exclude");
	
	if (verbose > 2) {
		rprintf(FINFO,"add_exclude(%s,%s)\n",pattern,
			      include ? "include" : "exclude");
	}

	(*list)[len+1] = NULL;
}