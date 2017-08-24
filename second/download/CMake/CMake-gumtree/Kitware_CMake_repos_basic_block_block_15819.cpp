(strcmp(key, "boot-info-table") == 0) {
			iso9660->opt.boot_info_table = value != NULL;
			return (ARCHIVE_OK);
		}