int main(int argc, const char **argv)
{
	const char *usage =
		"usage: git credential-osxkeychain <get|store|erase>";

	if (!argv[1])
		die(usage);

	read_credential();

	if (!strcmp(argv[1], "get"))
		find_internet_password();
	else if (!strcmp(argv[1], "store"))
		add_internet_password();
	else if (!strcmp(argv[1], "erase"))
		delete_internet_password();
	/* otherwise, ignore unknown action */

	return 0;
}