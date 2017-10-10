	if (!(ls_options & LS_NAME_ONLY)) {
		if (ls_options & LS_SHOW_SIZE) {
			char size_text[24];
			if (!strcmp(type, blob_type)) {
				unsigned long size;
				if (sha1_object_info(sha1, &size) == OBJ_BAD)
					strcpy(size_text, "BAD");
				else
					snprintf(size_text, sizeof(size_text),
						 "%lu", size);
			} else
				strcpy(size_text, "-");
			printf("%06o %s %s %7s\t", mode, type,
			       find_unique_abbrev(sha1, abbrev),
			       size_text);
		} else
			printf("%06o %s %s\t", mode, type,
			       find_unique_abbrev(sha1, abbrev));
