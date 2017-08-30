			else
				ret = ARCHIVE_FATAL;
		}
	} else
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "tar: unknown keyword ``%s''", key);

	return (ret);
}

/* utility function- this exists to centralize the logic of tracking
