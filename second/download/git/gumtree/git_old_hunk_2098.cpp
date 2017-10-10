	argv_array_clear(&cmd->env_array);
	return ret;
}

int run_command(struct child_process *cmd)
{
	int code = start_command(cmd);
	if (code)
		return code;
	return finish_command(cmd);
}

int run_command_v_opt(const char **argv, int opt)
