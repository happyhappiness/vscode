	copy_le32(trailer.magic, 0x06054b50);
	copy_le16(trailer.disk, 0);
	copy_le16(trailer.directory_start_disk, 0);
	copy_le16_clamp(trailer.entries_on_this_disk, zip_dir_entries,
			&clamped);
	copy_le16_clamp(trailer.entries, zip_dir_entries, &clamped);
	copy_le32(trailer.size, zip_dir_offset);
	copy_le32(trailer.offset, zip_offset);
	copy_le16(trailer.comment_length, sha1 ? GIT_SHA1_HEXSZ : 0);

	write_or_die(1, zip_dir, zip_dir_offset);
	if (clamped)
		write_zip64_trailer();
	write_or_die(1, &trailer, ZIP_DIR_TRAILER_SIZE);
	if (sha1)
		write_or_die(1, sha1_to_hex(sha1), GIT_SHA1_HEXSZ);
}

static void dos_time(time_t *time, int *dos_date, int *dos_time)
{
	struct tm *t = localtime(time);

	*dos_date = t->tm_mday + (t->tm_mon + 1) * 32 +
	            (t->tm_year + 1900 - 1980) * 512;
	*dos_time = t->tm_sec / 2 + t->tm_min * 32 + t->tm_hour * 2048;
}

