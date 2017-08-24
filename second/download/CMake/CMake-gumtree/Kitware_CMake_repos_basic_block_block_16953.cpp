{
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