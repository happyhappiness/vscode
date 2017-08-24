{
		attr = malloc(sizeof*(attr));
		name = strdup(atts[0]);
		value = strdup(atts[1]);
		if (attr == NULL || name == NULL || value == NULL) {
			archive_set_error(&a->archive, ENOMEM, "Out of memory");
			free(attr);
			free(name);
			free(value);
			return (ARCHIVE_FATAL);
		}
		attr->name = name;
		attr->value = value;
		attr->next = NULL;
		*list->last = attr;
		list->last = &(attr->next);
		atts += 2;
	}