{
		const char *name;
		const void *value;
		char *url_encoded_name = NULL, *encoded_name = NULL;
		size_t size;
		int r;

		archive_entry_xattr_next(entry, &name, &value, &size);
		url_encoded_name = url_encode(name);
		if (url_encoded_name != NULL) {
			/* Convert narrow-character to UTF-8. */
			r = archive_strcpy_l(&(pax->l_url_encoded_name),
			    url_encoded_name, pax->sconv_utf8);
			free(url_encoded_name); /* Done with this. */
			if (r == 0)
				encoded_name = pax->l_url_encoded_name.s;
			else if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Linkname");
				return (ARCHIVE_FATAL);
			}
		}

		archive_write_pax_header_xattr(pax, encoded_name,
		    value, size);

	}