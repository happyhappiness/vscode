		size = buf.len;
	}
	if (write_in_full(fd, blob, size) != size)
		die_errno("unable to write temp-file");
	close_tempfile(&temp->tempfile);
	temp->name = get_tempfile_path(&temp->tempfile);
	sha1_to_hex_r(temp->hex, sha1);
	xsnprintf(temp->mode, sizeof(temp->mode), "%06o", mode);
	strbuf_release(&buf);
	strbuf_release(&template);
	free(path_dup);
}

static struct diff_tempfile *prepare_temp_file(const char *name,
