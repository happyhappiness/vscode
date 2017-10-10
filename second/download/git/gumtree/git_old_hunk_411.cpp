		/* git push info */
		if (states.remote->mirror)
			printf_ln(_("  Local refs will be mirrored by 'git push'"));

		info.width = info.width2 = 0;
		for_each_string_list(&states.push, add_push_to_show_info, &info);
		qsort(info.list->items, info.list->nr,
			sizeof(*info.list->items), cmp_string_with_push);
		if (info.list->nr)
			printf_ln(Q_("  Local ref configured for 'git push'%s:",
				     "  Local refs configured for 'git push'%s:",
				     info.list->nr),
				  no_query ? _(" (status not queried)") : "");
		for_each_string_list(info.list, show_push_info_item, &info);
