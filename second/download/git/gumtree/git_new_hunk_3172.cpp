			item->string);
		return 0;
	}

	printf("    %-*s ", show_info->width, item->string);
	if (branch_info->rebase) {
		printf_ln(_(branch_info->rebase == INTERACTIVE_REBASE ?
			"rebases interactively onto remote %s" :
			"rebases onto remote %s"), merge->items[0].string);
		return 0;
	} else if (show_info->any_rebase) {
		printf_ln(_(" merges with remote %s"), merge->items[0].string);
		also = _("    and with remote");
	} else {
		printf_ln(_("merges with remote %s"), merge->items[0].string);
