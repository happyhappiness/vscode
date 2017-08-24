{
			close(data->child_stdout);
			data->child_stdout = -1;
			fcntl(data->child_stdin, F_SETFL, 0);
			continue;
		}