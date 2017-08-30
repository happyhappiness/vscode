		else
			archive_set_error(a, errno, "Can't stat '%s'",
			    filename);
		goto fail;
	}

	/*
