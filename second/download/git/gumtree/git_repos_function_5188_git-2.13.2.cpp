static void finalize_deferred_config(struct wt_status *s)
{
	int use_deferred_config = (status_format != STATUS_FORMAT_PORCELAIN &&
				   status_format != STATUS_FORMAT_PORCELAIN_V2 &&
				   !s->null_termination);

	if (s->null_termination) {
		if (status_format == STATUS_FORMAT_NONE ||
		    status_format == STATUS_FORMAT_UNSPECIFIED)
			status_format = STATUS_FORMAT_PORCELAIN;
		else if (status_format == STATUS_FORMAT_LONG)
			die(_("--long and -z are incompatible"));
	}

	if (use_deferred_config && status_format == STATUS_FORMAT_UNSPECIFIED)
		status_format = status_deferred_config.status_format;
	if (status_format == STATUS_FORMAT_UNSPECIFIED)
		status_format = STATUS_FORMAT_NONE;

	if (use_deferred_config && s->show_branch < 0)
		s->show_branch = status_deferred_config.show_branch;
	if (s->show_branch < 0)
		s->show_branch = 0;
}