(version == 1 && data_length == 8) {
					file->cl_offset = (uint64_t)
					    iso9660->logical_block_size *
					    (uint64_t)archive_le32dec(data);
					iso9660->seenRockridge = 1;
				}