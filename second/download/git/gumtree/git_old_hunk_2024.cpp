			buffer = sha1_file_to_archive(args, path, sha1, mode,
						      &type, &size);
			if (!buffer)
				return error("cannot read %s",
					     sha1_to_hex(sha1));
			crc = crc32(crc, buffer, size);
			out = buffer;
		}
		compressed_size = (method == 0) ? size : 0;
	} else {
		return error("unsupported file mode: 0%o (SHA1: %s)", mode,
				sha1_to_hex(sha1));
