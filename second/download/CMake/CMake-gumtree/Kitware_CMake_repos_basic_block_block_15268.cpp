{
		if (mode != mode_final) {
			le = new_fixup(a, path);
			le->fixup |=TODO_MODE_BASE;
			le->mode = mode_final;
		}
		free(full);
		return (ARCHIVE_OK);
	}