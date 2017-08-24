{
				if (datasize < 4)
					break;
				zip_entry->atime = archive_le32dec(p + offset);
				offset += 4;
				datasize -= 4;
			}