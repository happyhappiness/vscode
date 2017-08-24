(zip->hctx_valid) {
				r = check_authentication_code(a, NULL);
				if (r != ARCHIVE_OK)
					return (r);
			}