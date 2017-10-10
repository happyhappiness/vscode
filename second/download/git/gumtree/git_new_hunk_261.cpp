					on_what = _("HEAD detached from ");
			} else {
				branch_name = "";
				on_what = _("Not currently on any branch.");
			}
		}
		status_printf(s, color(WT_STATUS_HEADER, s), "%s", "");
		status_printf_more(s, branch_status_color, "%s", on_what);
		status_printf_more(s, branch_color, "%s\n", branch_name);
		if (!s->is_initial)
			wt_status_print_tracking(s);
	}

	wt_status_print_state(s, &state);
	free(state.branch);
	free(state.onto);
	free(state.detached_from);

	if (s->is_initial) {
		status_printf_ln(s, color(WT_STATUS_HEADER, s), "%s", "");
		status_printf_ln(s, color(WT_STATUS_HEADER, s), _("Initial commit"));
		status_printf_ln(s, color(WT_STATUS_HEADER, s), "%s", "");
	}

	wt_status_print_updated(s);
	wt_status_print_unmerged(s);
	wt_status_print_changed(s);
	if (s->submodule_summary &&
