
	*list = (struct exclude_struct **)Realloc(*list,sizeof(struct exclude_struct *)*(len+2));
	
	if (!*list || !((*list)[len] = make_exclude(pattern, include)))
		out_of_memory("add_exclude");
	
	if (verbose > 2) {
		rprintf(FINFO,"add_exclude(%s,%s)\n",pattern,
			      include ? "include" : "exclude");
	}

	(*list)[len+1] = NULL;
}

void add_exclude(const char *pattern, int include)
{
	add_exclude_list(pattern,&exclude_list, include);
