static void read_rr(struct string_list *rr)
{
	unsigned char sha1[20];
	char buf[PATH_MAX];
	FILE *in = fopen(git_path_merge_rr(), "r");
	if (!in)
		return;
	while (fread(buf, 40, 1, in) == 1) {
		int i;
		char *name;
		if (get_sha1_hex(buf, sha1))
			die("corrupt MERGE_RR");
		buf[40] = '\0';
		name = xstrdup(buf);
		if (fgetc(in) != '\t')
			die("corrupt MERGE_RR");
		for (i = 0; i < sizeof(buf); i++) {
			int c = fgetc(in);
			if (c < 0)
				die("corrupt MERGE_RR");
			buf[i] = c;
			if (c == 0)
				 break;
		}
		if (i == sizeof(buf))
			die("filename too long");
		string_list_insert(rr, buf)->util = name;
	}
	fclose(in);
}