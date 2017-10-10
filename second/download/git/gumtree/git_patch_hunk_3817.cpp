 static unsigned int pack_open_fds;
 static unsigned int pack_max_fds;
 static size_t peak_pack_mapped;
 static size_t pack_mapped;
 struct packed_git *packed_git;
 
+static struct mru packed_git_mru_storage;
+struct mru *packed_git_mru = &packed_git_mru_storage;
+
 void pack_report(void)
 {
 	fprintf(stderr,
 		"pack_report: getpagesize()            = %10" SZ_FMT "\n"
 		"pack_report: core.packedGitWindowSize = %10" SZ_FMT "\n"
 		"pack_report: core.packedGitLimit      = %10" SZ_FMT "\n",
