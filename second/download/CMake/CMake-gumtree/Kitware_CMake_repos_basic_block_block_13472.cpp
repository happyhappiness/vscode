{
				zip_entry->atime = archive_le32dec(p + offset);
				zip_entry->mtime =
				    archive_le32dec(p + offset + 4);
			}