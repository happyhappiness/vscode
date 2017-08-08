{
			err = set_conversion_failed_error(a, tar->sconv,
			    "Linkname");
			if (err == ARCHIVE_FATAL)
				return (err);
		}