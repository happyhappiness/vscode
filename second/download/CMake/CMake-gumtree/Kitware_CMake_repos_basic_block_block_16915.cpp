{
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