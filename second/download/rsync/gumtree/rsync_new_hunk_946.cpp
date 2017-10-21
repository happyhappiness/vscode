				file->flags &= ~FLAG_CONTENT_DIR;
			send1extra(f, file, flist);
			prev_flags = file->flags;
			dp = F_DIR_NODE_P(file);
		}

		if (io_error == save_io_error || ignore_errors)
			write_byte(f, 0);
		else if (use_safe_inc_flist) {
			write_shortint(f, XMIT_EXTENDED_FLAGS|XMIT_IO_ERROR_ENDLIST);
			write_varint(f, io_error);
		} else {
			if (delete_during)
				fatal_unsafe_io_error();
			write_byte(f, 0);
		}

		if (need_unsorted_flist) {
			if (!(flist->sorted = new_array(struct file_struct *, flist->used)))
				out_of_memory("send_extra_file_list");
			memcpy(flist->sorted, flist->files,
			       flist->used * sizeof (struct file_struct*));
