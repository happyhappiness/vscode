{
		iso9660->logical_block_size = logical_block_size;
		iso9660->volume_block = volume_block;
		iso9660->volume_size =
		    logical_block_size * (uint64_t)volume_block;
		iso9660->primary.location =
		    archive_le32dec(p + DR_extent_offset);
		iso9660->primary.size = archive_le32dec(p + DR_size_offset);
	}