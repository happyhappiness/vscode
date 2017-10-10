			status_printf_ln(s, color,
				_("  (use \"git commit --amend\" to amend the current commit)"));
			status_printf_ln(s, color,
				_("  (use \"git rebase --continue\" once you are satisfied with your changes)"));
		}
	}
	wt_longstatus_print_trailer(s);
}

static void show_cherry_pick_in_progress(struct wt_status *s,
					struct wt_status_state *state,
					const char *color)
{
