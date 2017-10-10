
static int show_local_info_item(struct string_list_item *item, void *cb_data)
{
	struct show_info *show_info = cb_data;
	struct branch_info *branch_info = item->util;
	struct string_list *merge = &branch_info->merge;
	int width = show_info->width + 4;
	int i;

	if (branch_info->rebase && branch_info->merge.nr > 1) {
		error(_("invalid branch.%s.merge; cannot rebase onto > 1 branch"),
			item->string);
		return 0;
	}

	printf("    %-*s ", show_info->width, item->string);
	if (branch_info->rebase) {
		printf_ln(branch_info->rebase == INTERACTIVE_REBASE
			  ? _("rebases interactively onto remote %s")
			  : _("rebases onto remote %s"), merge->items[0].string);
		return 0;
	} else if (show_info->any_rebase) {
		printf_ln(_(" merges with remote %s"), merge->items[0].string);
		width++;
	} else {
		printf_ln(_("merges with remote %s"), merge->items[0].string);
	}
	for (i = 1; i < merge->nr; i++)
		printf(_("%-*s    and with remote %s\n"), width, "",
		       merge->items[i].string);

	return 0;
}

static int add_push_to_show_info(struct string_list_item *push_item, void *cb_data)
