static int
pax_attribute(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const char *key, const char *value)
{
	int64_t s;
	long n;
	int err = ARCHIVE_OK, r;

	if (value == NULL)
		value = "";	/* Disable compiler warning; do not pass
				 * NULL pointer to strlen().  */
	switch (key[0]) {
	case 'G':
		/* GNU "0.0" sparse pax format. */
		if (strcmp(key, "GNU.sparse.numblocks") == 0) {
			tar->sparse_offset = -1;
			tar->sparse_numbytes = -1;
			tar->sparse_gnu_major = 0;
			tar->sparse_gnu_minor = 0;
		}
		if (strcmp(key, "GNU.sparse.offset") == 0) {
			tar->sparse_offset = tar_atol10(value, strlen(value));
			if (tar->sparse_numbytes != -1) {
				if (gnu_add_sparse_entry(a, tar,
				    tar->sparse_offset, tar->sparse_numbytes)
				    != ARCHIVE_OK)
					return (ARCHIVE_FATAL);
				tar->sparse_offset = -1;
				tar->sparse_numbytes = -1;
			}
		}
		if (strcmp(key, "GNU.sparse.numbytes") == 0) {
			tar->sparse_numbytes = tar_atol10(value, strlen(value));
			if (tar->sparse_numbytes != -1) {
				if (gnu_add_sparse_entry(a, tar,
				    tar->sparse_offset, tar->sparse_numbytes)
				    != ARCHIVE_OK)
					return (ARCHIVE_FATAL);
				tar->sparse_offset = -1;
				tar->sparse_numbytes = -1;
			}
		}
		if (strcmp(key, "GNU.sparse.size") == 0) {
			tar->realsize = tar_atol10(value, strlen(value));
			archive_entry_set_size(entry, tar->realsize);
		}

		/* GNU "0.1" sparse pax format. */
		if (strcmp(key, "GNU.sparse.map") == 0) {
			tar->sparse_gnu_major = 0;
			tar->sparse_gnu_minor = 1;
			if (gnu_sparse_01_parse(a, tar, value) != ARCHIVE_OK)
				return (ARCHIVE_WARN);
		}

		/* GNU "1.0" sparse pax format */
		if (strcmp(key, "GNU.sparse.major") == 0) {
			tar->sparse_gnu_major = (int)tar_atol10(value, strlen(value));
			tar->sparse_gnu_pending = 1;
		}
		if (strcmp(key, "GNU.sparse.minor") == 0) {
			tar->sparse_gnu_minor = (int)tar_atol10(value, strlen(value));
			tar->sparse_gnu_pending = 1;
		}
		if (strcmp(key, "GNU.sparse.name") == 0) {
			/*
			 * The real filename; when storing sparse
			 * files, GNU tar puts a synthesized name into
			 * the regular 'path' attribute in an attempt
			 * to limit confusion. ;-)
			 */
			archive_strcpy(&(tar->entry_pathname_override), value);
		}
		if (strcmp(key, "GNU.sparse.realsize") == 0) {
			tar->realsize = tar_atol10(value, strlen(value));
			archive_entry_set_size(entry, tar->realsize);
		}
		break;
	case 'L':
		/* Our extensions */
/* TODO: Handle arbitrary extended attributes... */
/*
		if (strcmp(key, "LIBARCHIVE.xxxxxxx") == 0)
			archive_entry_set_xxxxxx(entry, value);
*/
		if (strcmp(key, "LIBARCHIVE.creationtime") == 0) {
			pax_time(value, &s, &n);
			archive_entry_set_birthtime(entry, s, n);
		}
		if (memcmp(key, "LIBARCHIVE.xattr.", 17) == 0)
			pax_attribute_xattr(entry, key, value);
		break;
	case 'S':
		/* We support some keys used by the "star" archiver */
		if (strcmp(key, "SCHILY.acl.access") == 0) {
			if (tar->sconv_acl == NULL) {
				tar->sconv_acl =
				    archive_string_conversion_from_charset(
					&(a->archive), "UTF-8", 1);
				if (tar->sconv_acl == NULL)
					return (ARCHIVE_FATAL);
			}

			r = archive_acl_parse_l(archive_entry_acl(entry),
			    value, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
			    tar->sconv_acl);
			if (r != ARCHIVE_OK) {
				err = r;
				if (err == ARCHIVE_FATAL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate memory for "
					    "SCHILY.acl.access");
					return (err);
				}
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Parse error: SCHILY.acl.access");
			}
		} else if (strcmp(key, "SCHILY.acl.default") == 0) {
			if (tar->sconv_acl == NULL) {
				tar->sconv_acl =
				    archive_string_conversion_from_charset(
					&(a->archive), "UTF-8", 1);
				if (tar->sconv_acl == NULL)
					return (ARCHIVE_FATAL);
			}

			r = archive_acl_parse_l(archive_entry_acl(entry),
			    value, ARCHIVE_ENTRY_ACL_TYPE_DEFAULT,
			    tar->sconv_acl);
			if (r != ARCHIVE_OK) {
				err = r;
				if (err == ARCHIVE_FATAL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate memory for "
					    "SCHILY.acl.default");
					return (err);
				}
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Parse error: SCHILY.acl.default");
			}
		} else if (strcmp(key, "SCHILY.devmajor") == 0) {
			archive_entry_set_rdevmajor(entry,
			    (dev_t)tar_atol10(value, strlen(value)));
		} else if (strcmp(key, "SCHILY.devminor") == 0) {
			archive_entry_set_rdevminor(entry,
			    (dev_t)tar_atol10(value, strlen(value)));
		} else if (strcmp(key, "SCHILY.fflags") == 0) {
			archive_entry_copy_fflags_text(entry, value);
		} else if (strcmp(key, "SCHILY.dev") == 0) {
			archive_entry_set_dev(entry,
			    (dev_t)tar_atol10(value, strlen(value)));
		} else if (strcmp(key, "SCHILY.ino") == 0) {
			archive_entry_set_ino(entry,
			    tar_atol10(value, strlen(value)));
		} else if (strcmp(key, "SCHILY.nlink") == 0) {
			archive_entry_set_nlink(entry, (unsigned)
			    tar_atol10(value, strlen(value)));
		} else if (strcmp(key, "SCHILY.realsize") == 0) {
			tar->realsize = tar_atol10(value, strlen(value));
			archive_entry_set_size(entry, tar->realsize);
		} else if (strcmp(key, "SUN.holesdata") == 0) {
			/* A Solaris extension for sparse. */
			r = solaris_sparse_parse(a, tar, entry, value);
			if (r < err) {
				if (r == ARCHIVE_FATAL)
					return (r);
				err = r;
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Parse error: SUN.holesdata");
			}
		}
		break;
	case 'a':
		if (strcmp(key, "atime") == 0) {
			pax_time(value, &s, &n);
			archive_entry_set_atime(entry, s, n);
		}
		break;
	case 'c':
		if (strcmp(key, "ctime") == 0) {
			pax_time(value, &s, &n);
			archive_entry_set_ctime(entry, s, n);
		} else if (strcmp(key, "charset") == 0) {
			/* TODO: Publish charset information in entry. */
		} else if (strcmp(key, "comment") == 0) {
			/* TODO: Publish comment in entry. */
		}
		break;
	case 'g':
		if (strcmp(key, "gid") == 0) {
			archive_entry_set_gid(entry,
			    tar_atol10(value, strlen(value)));
		} else if (strcmp(key, "gname") == 0) {
			archive_strcpy(&(tar->entry_gname), value);
		}
		break;
	case 'h':
		if (strcmp(key, "hdrcharset") == 0) {
			if (strcmp(value, "BINARY") == 0)
				/* Binary  mode. */
				tar->pax_hdrcharset_binary = 1;
			else if (strcmp(value, "ISO-IR 10646 2000 UTF-8") == 0)
				tar->pax_hdrcharset_binary = 0;
		}
		break;
	case 'l':
		/* pax interchange doesn't distinguish hardlink vs. symlink. */
		if (strcmp(key, "linkpath") == 0) {
			archive_strcpy(&(tar->entry_linkpath), value);
		}
		break;
	case 'm':
		if (strcmp(key, "mtime") == 0) {
			pax_time(value, &s, &n);
			archive_entry_set_mtime(entry, s, n);
		}
		break;
	case 'p':
		if (strcmp(key, "path") == 0) {
			archive_strcpy(&(tar->entry_pathname), value);
		}
		break;
	case 'r':
		/* POSIX has reserved 'realtime.*' */
		break;
	case 's':
		/* POSIX has reserved 'security.*' */
		/* Someday: if (strcmp(key, "security.acl") == 0) { ... } */
		if (strcmp(key, "size") == 0) {
			/* "size" is the size of the data in the entry. */
			tar->entry_bytes_remaining
			    = tar_atol10(value, strlen(value));
			/*
			 * But, "size" is not necessarily the size of
			 * the file on disk; if this is a sparse file,
			 * the disk size may have already been set from
			 * GNU.sparse.realsize or GNU.sparse.size or
			 * an old GNU header field or SCHILY.realsize
			 * or ....
			 */
			if (tar->realsize < 0) {
				archive_entry_set_size(entry,
				    tar->entry_bytes_remaining);
				tar->realsize
				    = tar->entry_bytes_remaining;
			}
		}
		break;
	case 'u':
		if (strcmp(key, "uid") == 0) {
			archive_entry_set_uid(entry,
			    tar_atol10(value, strlen(value)));
		} else if (strcmp(key, "uname") == 0) {
			archive_strcpy(&(tar->entry_uname), value);
		}
		break;
	}
	return (err);
}