				file->flags &= ~FLAG_CONTENT_DIR;
			send1extra(f, file, flist);
			prev_flags = file->flags;
			dp = F_DIR_NODE_P(file);
		}

		write_byte(f, 0);

		if (need_unsorted_flist) {
			if (!(flist->sorted = new_array(struct file_struct *, flist->used)))
				out_of_memory("send_extra_file_list");
			memcpy(flist->sorted, flist->files,
			       flist->used * sizeof (struct file_struct*));
