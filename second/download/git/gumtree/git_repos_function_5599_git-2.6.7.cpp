static void write_pack_file(void)
{
	uint32_t i = 0, j;
	struct sha1file *f;
	off_t offset;
	uint32_t nr_remaining = nr_result;
	time_t last_mtime = 0;
	struct object_entry **write_order;

	if (progress > pack_to_stdout)
		progress_state = start_progress(_("Writing objects"), nr_result);
	written_list = xmalloc(to_pack.nr_objects * sizeof(*written_list));
	write_order = compute_write_order();

	do {
		unsigned char sha1[20];
		char *pack_tmp_name = NULL;

		if (pack_to_stdout)
			f = sha1fd_throughput(1, "<stdout>", progress_state);
		else
			f = create_tmp_packfile(&pack_tmp_name);

		offset = write_pack_header(f, nr_remaining);

		if (reuse_packfile) {
			off_t packfile_size;
			assert(pack_to_stdout);

			packfile_size = write_reused_pack(f);
			offset += packfile_size;
		}

		nr_written = 0;
		for (; i < to_pack.nr_objects; i++) {
			struct object_entry *e = write_order[i];
			if (write_one(f, e, &offset) == WRITE_ONE_BREAK)
				break;
			display_progress(progress_state, written);
		}

		/*
		 * Did we write the wrong # entries in the header?
		 * If so, rewrite it like in fast-import
		 */
		if (pack_to_stdout) {
			sha1close(f, sha1, CSUM_CLOSE);
		} else if (nr_written == nr_remaining) {
			sha1close(f, sha1, CSUM_FSYNC);
		} else {
			int fd = sha1close(f, sha1, 0);
			fixup_pack_header_footer(fd, sha1, pack_tmp_name,
						 nr_written, sha1, offset);
			close(fd);
			write_bitmap_index = 0;
		}

		if (!pack_to_stdout) {
			struct stat st;
			struct strbuf tmpname = STRBUF_INIT;

			/*
			 * Packs are runtime accessed in their mtime
			 * order since newer packs are more likely to contain
			 * younger objects.  So if we are creating multiple
			 * packs then we should modify the mtime of later ones
			 * to preserve this property.
			 */
			if (stat(pack_tmp_name, &st) < 0) {
				warning("failed to stat %s: %s",
					pack_tmp_name, strerror(errno));
			} else if (!last_mtime) {
				last_mtime = st.st_mtime;
			} else {
				struct utimbuf utb;
				utb.actime = st.st_atime;
				utb.modtime = --last_mtime;
				if (utime(pack_tmp_name, &utb) < 0)
					warning("failed utime() on %s: %s",
						pack_tmp_name, strerror(errno));
			}

			strbuf_addf(&tmpname, "%s-", base_name);

			if (write_bitmap_index) {
				bitmap_writer_set_checksum(sha1);
				bitmap_writer_build_type_index(written_list, nr_written);
			}

			finish_tmp_packfile(&tmpname, pack_tmp_name,
					    written_list, nr_written,
					    &pack_idx_opts, sha1);

			if (write_bitmap_index) {
				strbuf_addf(&tmpname, "%s.bitmap", sha1_to_hex(sha1));

				stop_progress(&progress_state);

				bitmap_writer_show_progress(progress);
				bitmap_writer_reuse_bitmaps(&to_pack);
				bitmap_writer_select_commits(indexed_commits, indexed_commits_nr, -1);
				bitmap_writer_build(&to_pack);
				bitmap_writer_finish(written_list, nr_written,
						     tmpname.buf, write_bitmap_options);
				write_bitmap_index = 0;
			}

			strbuf_release(&tmpname);
			free(pack_tmp_name);
			puts(sha1_to_hex(sha1));
		}

		/* mark written objects as written to previous pack */
		for (j = 0; j < nr_written; j++) {
			written_list[j]->offset = (off_t)-1;
		}
		nr_remaining -= nr_written;
	} while (nr_remaining && i < to_pack.nr_objects);

	free(written_list);
	free(write_order);
	stop_progress(&progress_state);
	if (written != nr_result)
		die("wrote %"PRIu32" objects while expecting %"PRIu32,
			written, nr_result);
}