printf_ln(_(branch_info->rebase == INTERACTIVE_REBASE ?
			"rebases interactively onto remote %s" :
			"rebases onto remote %s"), merge->items[0].string);