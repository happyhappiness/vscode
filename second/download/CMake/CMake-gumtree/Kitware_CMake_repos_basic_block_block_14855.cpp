{
		const void *metadata;
		size_t metadata_size;
		metadata = archive_entry_mac_metadata(a->entry, &metadata_size);
		if (metadata != NULL && metadata_size > 0) {
			int r2 = set_mac_metadata(a, archive_entry_pathname(
			    a->entry), metadata, metadata_size);
			if (r2 < ret) ret = r2;
		}
	}