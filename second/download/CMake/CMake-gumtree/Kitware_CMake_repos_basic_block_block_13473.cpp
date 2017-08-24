{
				if (datasize < 4)
					break;
				zip_entry->ctime = archive_le32dec(p + offset);
				offset += 4;
				datasize -= 4;
			}