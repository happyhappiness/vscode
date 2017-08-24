{
		archive_string_init(&s);
		archive_strcpy(&s, "SCHILY.xattr.");
		archive_strcat(&s, encoded_name);
		add_pax_attr_binary(&(pax->pax_header), s.s, value, value_len);
		archive_string_free(&s);
	}