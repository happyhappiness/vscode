 
 int main(int argc, const char **argv)
 {
 	struct strbuf buf = STRBUF_INIT;
 	int nongit;
 
+	git_setup_gettext();
+
 	git_extract_argv0_path(argv[0]);
 	setup_git_directory_gently(&nongit);
 	if (argc < 2) {
 		error("remote-curl: usage: git remote-curl <remote> [<url>]");
 		return 1;
 	}
