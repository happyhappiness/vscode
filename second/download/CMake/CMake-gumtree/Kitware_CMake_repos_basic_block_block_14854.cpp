{
			int r2 = set_mac_metadata(a, archive_entry_pathname(
			    a->entry), metadata, metadata_size);
			if (r2 < ret) ret = r2;
		}