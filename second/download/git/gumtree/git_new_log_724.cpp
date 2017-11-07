fprintf(stderr, _("Failed to fstat %s: %s"),
			get_tempfile_path(&log_lock.tempfile),
			strerror(saved_errno));