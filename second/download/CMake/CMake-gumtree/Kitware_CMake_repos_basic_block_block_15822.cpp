(strcmp(key, "boot") == 0) {
			if (value == NULL)
				iso9660->opt.boot = 0;
			else {
				iso9660->opt.boot = 1;
				archive_strcpy(
				    &(iso9660->el_torito.boot_filename),
				    value);
			}
			return (ARCHIVE_OK);
		}