static int filter_by_patterns_cmd(void)
{
	struct dir_struct dir;
	struct strbuf confirm = STRBUF_INIT;
	struct strbuf **ignore_list;
	struct string_list_item *item;
	struct exclude_list *el;
	int changed = -1, i;

	for (;;) {
		if (!del_list.nr)
			break;

		if (changed)
			pretty_print_dels();

		clean_print_color(CLEAN_COLOR_PROMPT);
		printf(_("Input ignore patterns>> "));
		clean_print_color(CLEAN_COLOR_RESET);
		if (strbuf_getline_lf(&confirm, stdin) != EOF)
			strbuf_trim(&confirm);
		else
			putchar('\n');

		/* quit filter_by_pattern mode if press ENTER or Ctrl-D */
		if (!confirm.len)
			break;

		memset(&dir, 0, sizeof(dir));
		el = add_exclude_list(&dir, EXC_CMDL, "manual exclude");
		ignore_list = strbuf_split_max(&confirm, ' ', 0);

		for (i = 0; ignore_list[i]; i++) {
			strbuf_trim(ignore_list[i]);
			if (!ignore_list[i]->len)
				continue;

			add_exclude(ignore_list[i]->buf, "", 0, el, -(i+1));
		}

		changed = 0;
		for_each_string_list_item(item, &del_list) {
			int dtype = DT_UNKNOWN;

			if (is_excluded(&dir, &the_index, item->string, &dtype)) {
				*item->string = '\0';
				changed++;
			}
		}

		if (changed) {
			string_list_remove_empty_items(&del_list, 0);
		} else {
			clean_print_color(CLEAN_COLOR_ERROR);
			printf_ln(_("WARNING: Cannot find items matched by: %s"), confirm.buf);
			clean_print_color(CLEAN_COLOR_RESET);
		}

		strbuf_list_free(ignore_list);
		clear_directory(&dir);
	}

	strbuf_release(&confirm);
	return 0;
}