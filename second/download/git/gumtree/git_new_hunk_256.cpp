			status_printf_ln(s, c, _("  (use \"git add/rm <file>...\" as appropriate to mark resolution)"));
	} else if (!del_mod_conflict && !not_deleted) {
		status_printf_ln(s, c, _("  (use \"git rm <file>...\" to mark resolution)"));
	} else {
		status_printf_ln(s, c, _("  (use \"git add/rm <file>...\" as appropriate to mark resolution)"));
	}
	status_printf_ln(s, c, "%s", "");
}

static void wt_status_print_cached_header(struct wt_status *s)
{
	const char *c = color(WT_STATUS_HEADER, s);

