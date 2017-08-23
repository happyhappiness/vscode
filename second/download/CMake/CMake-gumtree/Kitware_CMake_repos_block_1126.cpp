{
			/*
			 * The only feasible separator is a final '/';
			 * this would result in a non-empty prefix and
			 * an empty name, which POSIX doesn't
			 * explicitly forbid, but it just feels wrong.
			 */
			archive_set_error(&a->archive, ENAMETOOLONG,
			    "Pathname too long");
			ret = ARCHIVE_FAILED;
		}