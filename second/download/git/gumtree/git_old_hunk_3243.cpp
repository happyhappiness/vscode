		return -1;
	}

	close(cmd->out);
	return finish_command(cmd);
}
