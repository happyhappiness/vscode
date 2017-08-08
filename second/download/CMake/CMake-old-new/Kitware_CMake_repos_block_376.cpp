{
			archive_set_error(&a->archive, errno,
			    "Failed to get metadata(xattr)");
			ret = ARCHIVE_WARN;
			goto exit_xattr;
		}