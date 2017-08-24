(uidsize == 4 && datasize >= 6)
						zip_entry->uid =
						    archive_le32dec(
						        p + offset + 2)