					editor);
	}

	if (!buffer)
		return 0;
	if (strbuf_read_file(buffer, path, 0) < 0)
		return error("could not read file '%s': %s",
				path, strerror(errno));
	return 0;
}
