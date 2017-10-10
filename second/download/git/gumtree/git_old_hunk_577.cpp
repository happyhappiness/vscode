		status_printf_ln(s, color,
			_("All conflicts fixed but you are still merging."));
		if (s->hints)
			status_printf_ln(s, color,
				_("  (use \"git commit\" to conclude merge)"));
	}
	wt_status_print_trailer(s);
}

static void show_am_in_progress(struct wt_status *s,
				struct wt_status_state *state,
				const char *color)
{
