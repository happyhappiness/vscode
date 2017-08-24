(a->skip_file_set &&
		    bhfi_dev(&a->st) == a->skip_file_dev &&
		    bhfi_ino(&a->st) == a->skip_file_ino) {
			archive_set_error(&a->archive, 0,
			    "Refusing to overwrite archive");
			return (ARCHIVE_FAILED);
		}