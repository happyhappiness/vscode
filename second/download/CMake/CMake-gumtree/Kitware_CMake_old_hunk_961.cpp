		(*last_entry)->next = entry;

	*last_entry = entry;



	len = strcspn(line, " \t\r\n");

	if ((entry->name = malloc(len + 1)) == NULL) {

		archive_set_error(&a->archive, errno, "Can't allocate memory");

		return (ARCHIVE_FATAL);

	}



	memcpy(entry->name, line, len);

	entry->name[len] = '\0';

	parse_escapes(entry->name, entry);



	line += len;

	for (iter = *global; iter != NULL; iter = iter->next) {

		r = add_option(a, &entry->options, iter->value,

		    strlen(iter->value));

