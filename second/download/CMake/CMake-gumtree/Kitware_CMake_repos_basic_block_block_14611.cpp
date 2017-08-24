(ret == 0) {
			close(data->child_stdin);
			data->child_stdin = -1;
			fcntl(data->child_stdout, F_SETFL, 0);
			return (0);
		}