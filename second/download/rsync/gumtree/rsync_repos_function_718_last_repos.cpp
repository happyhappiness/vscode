static int add_cnk_list_entry(struct pr_chunk_x **list,
				int max_num, struct pr_chunk *chunk) {
	struct pr_chunk_x *l;
	struct pr_chunk **c;
	int max;
	int cnum;
	int i, pos;

	if (chunk->num > max_num) {
		max = chunk->num;
	
		if (*list == NULL) {
			l = (struct pr_chunk_x *)malloc(sizeof(struct pr_chunk_x) * max);
			pos = 0;
		} else {
			l = (struct pr_chunk_x *)realloc(*list, sizeof(struct pr_chunk_x) * max);
			pos = max_num;
		}
		if (l == NULL) {
			for (i = 0; i < max; i++) {
				if ((*list)[i].chunks) free((*list)[i].chunks);
			}
			return 0;
		}
		for (i = pos; i < max; i++) {
			l[i].chunks = NULL;
			l[i].num = 0;
		}
	} else {
		l = *list;
		max = max_num;
	}

	i = chunk->num - 1;
	cnum = l[i].num + 1;
	if (l[i].chunks == NULL) {
		c = (struct pr_chunk **)malloc(sizeof(struct pr_chunk *) * cnum); 
	} else {
		c = (struct pr_chunk **)realloc(l[i].chunks, sizeof(struct pr_chunk *) * cnum);
	}
	if (c == NULL) {
		for (i = 0; i < max; i++) {
			if (l[i].chunks) free(l[i].chunks);
		}
		return 0;
	}
	c[l[i].num] = chunk;
	l[i].chunks = c;
	l[i].num = cnum;

	*list = l;
	return max;
}