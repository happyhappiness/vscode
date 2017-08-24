{
					/*
					 * CE extension comprises:
					 *   8 byte sector containing extension
					 *   8 byte offset w/in above sector
					 *   8 byte length of continuation
					 */
					int32_t location =
					    archive_le32dec(data);
					file->ce_offset =
					    archive_le32dec(data+8);
					file->ce_size =
					    archive_le32dec(data+16);
					if (register_CE(a, location, file)
					    != ARCHIVE_OK)
						return (ARCHIVE_FATAL);
				}