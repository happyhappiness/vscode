		}
	}

	r = zip_deflate_init(a, zip);
	if (r != ARCHIVE_OK)
		return (r);

	/*
	 * Note: '1' here is a performance optimization.
