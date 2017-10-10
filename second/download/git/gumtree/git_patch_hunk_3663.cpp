 static const char * const cherry_usage[] = {
 	N_("git cherry [-v] [<upstream> [<head> [<limit>]]]"),
 	NULL
 };
 
 static void print_commit(char sign, struct commit *commit, int verbose,
-			 int abbrev)
+			 int abbrev, FILE *file)
 {
 	if (!verbose) {
-		printf("%c %s\n", sign,
+		fprintf(file, "%c %s\n", sign,
 		       find_unique_abbrev(commit->object.oid.hash, abbrev));
 	} else {
 		struct strbuf buf = STRBUF_INIT;
 		pp_commit_easy(CMIT_FMT_ONELINE, commit, &buf);
-		printf("%c %s %s\n", sign,
+		fprintf(file, "%c %s %s\n", sign,
 		       find_unique_abbrev(commit->object.oid.hash, abbrev),
 		       buf.buf);
 		strbuf_release(&buf);
 	}
 }
 
