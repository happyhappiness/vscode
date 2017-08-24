{
		encoded_value = base64_encode((const char *)value, value_len);

		if (encoded_name != NULL && encoded_value != NULL) {
			archive_string_init(&s);
			archive_strcpy(&s, "LIBARCHIVE.xattr.");
			archive_strcat(&s, encoded_name);
			add_pax_attr(&(pax->pax_header), s.s, encoded_value);
			archive_string_free(&s);
		}
		free(encoded_value);
	}