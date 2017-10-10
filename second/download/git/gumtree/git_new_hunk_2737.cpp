				else
					on_what = _("HEAD detached from ");
			} else {
				branch_name = "";
				on_what = _("Not currently on any branch.");
			}
		} else
			skip_prefix(branch_name, "refs/heads/", &branch_name);
		status_printf(s, color(WT_STATUS_HEADER, s), "%s", "");
		status_printf_more(s, branch_status_color, "%s", on_what);
		status_printf_more(s, branch_color, "%s\n", branch_name);
		if (!s->is_initial)
			wt_status_print_tracking(s);
	}
