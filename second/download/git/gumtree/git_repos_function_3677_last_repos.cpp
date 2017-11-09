static int run_service_command(struct child_process *cld)
{
	argv_array_push(&cld->args, ".");
	cld->git_cmd = 1;
	cld->err = -1;
	if (start_command(cld))
		return -1;

	close(0);
	close(1);

	copy_to_log(cld->err);

	return finish_command(cld);
}