{
			bytes_read = read(data->child_stdout,
			    data->child_buf + data->child_buf_avail,
			    data->child_buf_len - data->child_buf_avail);
		}