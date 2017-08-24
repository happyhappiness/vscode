{
		do {
			ret = write(data->child_stdin, buf, buf_len);
		} while (ret == -1 && errno == EINTR);

		if (ret > 0)
			return (ret);
		if (ret == 0) {
			close(data->child_stdin);
			data->child_stdin = -1;
			fcntl(data->child_stdout, F_SETFL, 0);
			return (0);
		}
		if (ret == -1 && errno != EAGAIN)
			return (-1);

		if (data->child_stdout == -1) {
			fcntl(data->child_stdin, F_SETFL, 0);
			__archive_check_child(data->child_stdin,
				data->child_stdout);
			continue;
		}

		do {
			ret = read(data->child_stdout,
			    data->child_buf + data->child_buf_avail,
			    data->child_buf_len - data->child_buf_avail);
		} while (ret == -1 && errno == EINTR);

		if (ret == 0 || (ret == -1 && errno == EPIPE)) {
			close(data->child_stdout);
			data->child_stdout = -1;
			fcntl(data->child_stdin, F_SETFL, 0);
			continue;
		}
		if (ret == -1 && errno == EAGAIN) {
			__archive_check_child(data->child_stdin,
				data->child_stdout);
			continue;
		}
		if (ret == -1)
			return (-1);

		data->child_buf_avail += ret;

		ret = __archive_write_filter(f->next_filter,
		    data->child_buf, data->child_buf_avail);
		if (ret != ARCHIVE_OK)
			return (-1);
		data->child_buf_avail = 0;
	}