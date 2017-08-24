(a->archive.archive_format != ARCHIVE_FORMAT_TAR_PAX_RESTRICTED ||
	    need_extension) {
		if (archive_entry_mtime(entry_main) < 0  ||
		    archive_entry_mtime(entry_main) >= 0x7fffffff  ||
		    archive_entry_mtime_nsec(entry_main) != 0)
			add_pax_attr_time(&(pax->pax_header), "mtime",
			    archive_entry_mtime(entry_main),
			    archive_entry_mtime_nsec(entry_main));

		/* I use a star-compatible file flag attribute. */
		p = archive_entry_fflags_text(entry_main);
		if (p != NULL  &&  *p != '\0')
			add_pax_attr(&(pax->pax_header), "SCHILY.fflags", p);

		/* I use star-compatible ACL attributes. */
		if ((acl_types & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0) {
			ret = add_pax_acl(a, entry_original, pax,
			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA |
			    ARCHIVE_ENTRY_ACL_STYLE_COMPACT);
			if (ret == ARCHIVE_FATAL)
				return (ARCHIVE_FATAL);
		}
		if (acl_types & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) {
			ret = add_pax_acl(a, entry_original, pax,
			    ARCHIVE_ENTRY_ACL_TYPE_ACCESS |
			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA);
			if (ret == ARCHIVE_FATAL)
				return (ARCHIVE_FATAL);
		}
		if (acl_types & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) {
			ret = add_pax_acl(a, entry_original, pax,
			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT |
			    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID |
			    ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA);
			if (ret == ARCHIVE_FATAL)
				return (ARCHIVE_FATAL);
		}

		/* We use GNU-tar-compatible sparse attributes. */
		if (sparse_count > 0) {
			int64_t soffset, slength;

			add_pax_attr_int(&(pax->pax_header),
			    "GNU.sparse.major", 1);
			add_pax_attr_int(&(pax->pax_header),
			    "GNU.sparse.minor", 0);
			add_pax_attr(&(pax->pax_header),
			    "GNU.sparse.name", entry_name.s);
			add_pax_attr_int(&(pax->pax_header),
			    "GNU.sparse.realsize",
			    archive_entry_size(entry_main));

			/* Rename the file name which will be used for
			 * ustar header to a special name, which GNU
			 * PAX Format 1.0 requires */
			archive_entry_set_pathname(entry_main,
			    build_gnu_sparse_name(gnu_sparse_name,
			        entry_name.s));

			/*
			 * - Make a sparse map, which will precede a file data.
			 * - Get the total size of available data of sparse.
			 */
			archive_string_sprintf(&(pax->sparse_map), "%d\n",
			    sparse_count);
			while (archive_entry_sparse_next(entry_main,
			    &soffset, &slength) == ARCHIVE_OK) {
				archive_string_sprintf(&(pax->sparse_map),
				    "%jd\n%jd\n",
				    (intmax_t)soffset,
				    (intmax_t)slength);
				sparse_total += slength;
				if (sparse_list_add(pax, soffset, slength)
				    != ARCHIVE_OK) {
					archive_set_error(&a->archive,
					    ENOMEM,
					    "Can't allocate memory");
					archive_entry_free(entry_main);
					archive_string_free(&entry_name);
					return (ARCHIVE_FATAL);
				}
			}
		}

		/* Store extended attributes */
		if (archive_write_pax_header_xattrs(a, pax, entry_original)
		    == ARCHIVE_FATAL) {
			archive_entry_free(entry_main);
			archive_string_free(&entry_name);
			return (ARCHIVE_FATAL);
		}
	}