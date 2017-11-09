int child_main(int argc, char *argv[])
{
	start_server(STDIN_FILENO, STDOUT_FILENO, argc, argv);
	return 0;
}