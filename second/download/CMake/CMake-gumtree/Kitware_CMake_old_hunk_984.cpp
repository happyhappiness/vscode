			} else
				ret = ARCHIVE_FATAL;
		}
	} else
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "zip: unknown keyword ``%s''", key);

	return (ret);
}

static int
