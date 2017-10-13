printf_ln(branch_info->rebase == INTERACTIVE_REBASE
			  ? _("rebases interactively onto remote %s")
			  : _("rebases onto remote %s"), merge->items[0].string);