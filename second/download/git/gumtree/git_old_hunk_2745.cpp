			export_marks_file, strerror(saved_errno));
		return;
	}

	dump_marks_helper(f, 0, marks);
	if (commit_lock_file(&mark_lock)) {
		failure |= error("Unable to commit marks file %s: %s",
			export_marks_file, strerror(errno));
		return;
	}
}

static void read_marks(void)
