		(*last_entry)->next = entry;
	*last_entry = entry;

	if (is_form_d) {
		/*
		 * This form places the file name as last parameter.
		 */
		name = line + line_len -1;
		while (line_len > 0) {
			if (*name != '\r' && *name != '\n' &&
			    *name != '\t' && *name != ' ')
				break;
			name--;
			line_len--;
		}
		len = 0;
		while (line_len > 0) {
			if (*name == '\r' || *name == '\n' ||
			    *name == '\t' || *name == ' ') {
				name++;
				break;
			}
			name--;
			line_len--;
			len++;
		}
		end = name;
	} else {
		len = strcspn(line, " \t\r\n");
		name = line;
		line += len;
		end = line + line_len;
	}

	if ((entry->name = malloc(len + 1)) == NULL) {
		archive_set_error(&a->archive, errno, "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}

	memcpy(entry->name, name, len);
	entry->name[len] = '\0';
	parse_escapes(entry->name, entry);

	for (iter = *global; iter != NULL; iter = iter->next) {
		r = add_option(a, &entry->options, iter->value,
		    strlen(iter->value));
