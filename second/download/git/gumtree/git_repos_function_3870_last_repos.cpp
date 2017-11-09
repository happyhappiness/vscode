int check_pager_config(const char *cmd)
{
	struct pager_command_config_data data;

	data.cmd = cmd;
	data.want = -1;
	data.value = NULL;

	read_early_config(pager_command_config, &data);

	if (data.value)
		pager_program = data.value;
	return data.want;
}