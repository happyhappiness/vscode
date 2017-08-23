{
			archive_set_error(&a->archive, ENOMEM,
			    "Failed to get metadata(xattr)");
			ret = ARCHIVE_WARN;
			free(xattr_val_saved);
			goto exit_xattr;
		}