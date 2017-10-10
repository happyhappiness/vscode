		die_errno("unable to mkdir '%s'", dir);
	free(path_copy);
}

int main(int argc, const char **argv)
{
	static const char *usage[] = {
		"git-credential-cache--daemon [opts] <socket_path>",
		NULL
	};
	int debug = 0;
	const struct option options[] = {
