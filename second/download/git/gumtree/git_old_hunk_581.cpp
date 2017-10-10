		else
			status_printf_ln(s, color,
				_("  (all conflicts fixed: run \"git revert --continue\")"));
		status_printf_ln(s, color,
			_("  (use \"git revert --abort\" to cancel the revert operation)"));
	}
	wt_status_print_trailer(s);
}

static void show_bisect_in_progress(struct wt_status *s,
				struct wt_status_state *state,
				const char *color)
{
