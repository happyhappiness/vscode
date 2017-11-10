static int write_zip_entry(struct archiver_args *args,
			   const unsigned char *sha1,
			   const char *path, size_t pathlen,
			   unsigned int mode)
{
	struct zip_local_header header;
	struct zip_dir_header dirent;
	struct zip_extra_mtime extra;
	unsigned long attr2;
	unsigned long compressed_size;
	unsigned long crc;
	unsigned long direntsize;
	int method;
	unsigned char *out;
	void *deflated = NULL;
	void *buffer;
	struct git_istream *stream = NULL;
	unsigned long flags = 0;
	unsigned long size;
	int is_binary = -1;
	const char *path_without_prefix = path + args->baselen;
	unsigned int creator_version = 0;

	crc = crc32(0, NULL, 0);

	if (!has_only_ascii(path)) {
		if (is_utf8(path))
			flags |= ZIP_UTF8;
		else
			warning("Path is not valid UTF-8: %s", path);
	}

	if (pathlen > 0xffff) {
		return error("path too long (%d chars, SHA1: %s): %s",
				(int)pathlen, sha1_to_hex(sha1), path);
	}

	if (S_ISDIR(mode) || S_ISGITLINK(mode)) {
		method = 0;
		attr2 = 16;
		out = NULL;
		size = 0;
		compressed_size = 0;
		buffer = NULL;
	} else if (S_ISREG(mode) || S_ISLNK(mode)) {
		enum object_type type = sha1_object_info(sha1, &size);

		method = 0;
		attr2 = S_ISLNK(mode) ? ((mode | 0777) << 16) :
			(mode & 0111) ? ((mode) << 16) : 0;
		if (S_ISLNK(mode) || (mode & 0111))
			creator_version = 0x0317;
		if (S_ISREG(mode) && args->compression_level != 0 && size > 0)
			method = 8;

		if (S_ISREG(mode) && type == OBJ_BLOB && !args->convert &&
		    size > big_file_threshold) {
			stream = open_istream(sha1, &type, &size, NULL);
			if (!stream)
				return error("cannot stream blob %s",
					     sha1_to_hex(sha1));
			flags |= ZIP_STREAM;
			out = buffer = NULL;
		} else {
			buffer = sha1_file_to_archive(args, path, sha1, mode,
						      &type, &size);
			if (!buffer)
				return error("cannot read %s",
					     sha1_to_hex(sha1));
			crc = crc32(crc, buffer, size);
			is_binary = entry_is_binary(path_without_prefix,
						    buffer, size);
			out = buffer;
		}
		compressed_size = (method == 0) ? size : 0;
	} else {
		return error("unsupported file mode: 0%o (SHA1: %s)", mode,
				sha1_to_hex(sha1));
	}

	if (creator_version > max_creator_version)
		max_creator_version = creator_version;

	if (buffer && method == 8) {
		out = deflated = zlib_deflate_raw(buffer, size,
						  args->compression_level,
						  &compressed_size);
		if (!out || compressed_size >= size) {
			out = buffer;
			method = 0;
			compressed_size = size;
		}
	}

	copy_le16(extra.magic, 0x5455);
	copy_le16(extra.extra_size, ZIP_EXTRA_MTIME_PAYLOAD_SIZE);
	extra.flags[0] = 1;	/* just mtime */
	copy_le32(extra.mtime, args->time);

	/* make sure we have enough free space in the dictionary */
	direntsize = ZIP_DIR_HEADER_SIZE + pathlen + ZIP_EXTRA_MTIME_SIZE;
	while (zip_dir_size < zip_dir_offset + direntsize) {
		zip_dir_size += ZIP_DIRECTORY_MIN_SIZE;
		zip_dir = xrealloc(zip_dir, zip_dir_size);
	}

	copy_le32(dirent.magic, 0x02014b50);
	copy_le16(dirent.creator_version, creator_version);
	copy_le16(dirent.version, 10);
	copy_le16(dirent.flags, flags);
	copy_le16(dirent.compression_method, method);
	copy_le16(dirent.mtime, zip_time);
	copy_le16(dirent.mdate, zip_date);
	set_zip_dir_data_desc(&dirent, size, compressed_size, crc);
	copy_le16(dirent.filename_length, pathlen);
	copy_le16(dirent.extra_length, ZIP_EXTRA_MTIME_SIZE);
	copy_le16(dirent.comment_length, 0);
	copy_le16(dirent.disk, 0);
	copy_le32(dirent.attr2, attr2);
	copy_le32(dirent.offset, zip_offset);

	copy_le32(header.magic, 0x04034b50);
	copy_le16(header.version, 10);
	copy_le16(header.flags, flags);
	copy_le16(header.compression_method, method);
	copy_le16(header.mtime, zip_time);
	copy_le16(header.mdate, zip_date);
	set_zip_header_data_desc(&header, size, compressed_size, crc);
	copy_le16(header.filename_length, pathlen);
	copy_le16(header.extra_length, ZIP_EXTRA_MTIME_SIZE);
	write_or_die(1, &header, ZIP_LOCAL_HEADER_SIZE);
	zip_offset += ZIP_LOCAL_HEADER_SIZE;
	write_or_die(1, path, pathlen);
	zip_offset += pathlen;
	write_or_die(1, &extra, ZIP_EXTRA_MTIME_SIZE);
	zip_offset += ZIP_EXTR