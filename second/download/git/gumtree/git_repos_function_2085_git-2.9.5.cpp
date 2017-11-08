void clear_directory(struct dir_struct *dir)
{
	int i, j;
	struct exclude_list_group *group;
	struct exclude_list *el;
	struct exclude_stack *stk;

	for (i = EXC_CMDL; i <= EXC_FILE; i++) {
		group = &dir->exclude_list_group[i];
		for (j = 0; j < group->nr; j++) {
			el = &group->el[j];
			if (i == EXC_DIRS)
				free((char *)el->src);
			clear_exclude_list(el);
		}
		free(group->el);
	}

	stk = dir->exclude_stack;
	while (stk) {
		struct exclude_stack *prev = stk->prev;
		free(stk);
		stk = prev;
	}
	strbuf_release(&dir->basebuf);
}