int main(int argc, char **argv)
{
	unsigned char sha1[20];
	struct entry *entry;

	setup_git_directory();

	if (argc != 2)
		usage("git-convert-objects <sha1>");
	if (get_sha1(argv[1], sha1))
		die("Not a valid object name %s", argv[1]);

	entry = convert_entry(sha1);
	printf("new sha1: %s\n", sha1_to_hex(entry->new_sha1));
	return 0;
}