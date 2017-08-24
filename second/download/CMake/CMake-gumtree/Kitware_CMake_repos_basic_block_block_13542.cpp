{
			zip->end_of_entry = 1;
			if (zip->hctx_valid) {
				r = check_authentication_code(a, NULL);
				if (r != ARCHIVE_OK)
					return (r);
			}
			return (ARCHIVE_OK);
		}