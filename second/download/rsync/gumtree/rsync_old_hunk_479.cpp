		}
		free((*list));
		*list = NULL;
		return;
	}

	if (!*list) {
		*list = (struct exclude_struct **)malloc(sizeof(struct exclude_struct *)*2);
	} else {
		*list = (struct exclude_struct **)realloc(*list,sizeof(struct exclude_struct *)*(len+2));
	}
	
	if (!*list || !((*list)[len] = make_exclude(pattern, include)))
		out_of_memory("add_exclude");
	
	if (verbose > 2)
		rprintf(FINFO,"add_exclude(%s)\n",pattern);
