{
			archive_entry_set_is_metadata_encrypted(a->entry, 1);
			archive_entry_set_is_data_encrypted(a->entry, 1);
			zip->has_encrypted_entries = 1;
		}