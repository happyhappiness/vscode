(zip_entry != NULL) {
			next_zip_entry = zip_entry->next;
			archive_string_free(&zip_entry->rsrcname);
			free(zip_entry);
			zip_entry = next_zip_entry;
		}