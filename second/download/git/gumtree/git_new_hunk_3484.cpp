	if (has_unmerged(s)) {
		status_printf_ln(s, color, _("You have unmerged paths."));
		if (s->hints)
			status_printf_ln(s, color,
				_("  (fix conflicts and run \"git commit\")"));
	} else {
		s-> commitable = 1;
		status_printf_ln(s, color,
			_("All conflicts fixed but you are still merging."));
		if (s->hints)
			status_printf_ln(s, color,
				_("  (use \"git commit\" to conclude merge)"));
	}
