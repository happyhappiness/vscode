			ret = ARCHIVE_WARN;
			goto exit_xattr;
		}
		xattr_val_saved = xattr_val;
		xattr_val = realloc(xattr_val, s);
		if (xattr_val == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Failed to get metadata(xattr)");
			ret = ARCHIVE_WARN;
			free(xattr_val_saved);
			goto exit_xattr;
		}
		s = fgetxattr(tmpfd, xattr_names + xattr_i, xattr_val, s, 0, 0);