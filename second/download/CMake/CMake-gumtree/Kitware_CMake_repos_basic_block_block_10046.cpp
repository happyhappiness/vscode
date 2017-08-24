(a->extract == NULL) {
			archive_set_error(&a->archive, ENOMEM, "Can't extract");
			return (NULL);
		}