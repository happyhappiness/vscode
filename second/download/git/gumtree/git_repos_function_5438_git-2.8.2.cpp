static void create_output_file(const char *output_file)
{
	int output_fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (output_fd < 0)
		die_errno(_("could not create archive file '%s'"), output_file);
	if (output_fd != 1) {
		if (dup2(output_fd, 1) < 0)
			die_errno(_("could not redirect output"));
		else
			close(output_fd);
	}
}