(cab->bytes_skipped) {
			if (cab->entry_cfdata == NULL) {
				r = cab_next_cfdata(a);
				if (r < 0)
					return (r);
			}
			if (cab_consume_cfdata(a, cab->bytes_skipped) < 0)
				return (ARCHIVE_FATAL);
			cab->bytes_skipped = 0;
		}