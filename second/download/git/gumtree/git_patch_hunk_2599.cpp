 }
 
 static void dump_marks_helper(FILE *, uintmax_t, struct mark_set *);
 
 static void write_crash_report(const char *err)
 {
-	const char *loc = git_path("fast_import_crash_%"PRIuMAX, (uintmax_t) getpid());
+	char *loc = git_pathdup("fast_import_crash_%"PRIuMAX, (uintmax_t) getpid());
 	FILE *rpt = fopen(loc, "w");
 	struct branch *b;
 	unsigned long lu;
 	struct recent_command *rc;
 
 	if (!rpt) {
 		error("can't write crash report %s: %s", loc, strerror(errno));
+		free(loc);
 		return;
 	}
 
 	fprintf(stderr, "fast-import: dumping crash report to %s\n", loc);
 
 	fprintf(rpt, "fast-import crash report:\n");
 	fprintf(rpt, "    fast-import process: %"PRIuMAX"\n", (uintmax_t) getpid());
 	fprintf(rpt, "    parent process     : %"PRIuMAX"\n", (uintmax_t) getppid());
-	fprintf(rpt, "    at %s\n", show_date(time(NULL), 0, DATE_LOCAL));
+	fprintf(rpt, "    at %s\n", show_date(time(NULL), 0, DATE_MODE(LOCAL)));
 	fputc('\n', rpt);
 
 	fputs("fatal: ", rpt);
 	fputs(err, rpt);
 	fputc('\n', rpt);
 
