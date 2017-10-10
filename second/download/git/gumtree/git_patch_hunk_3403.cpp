 	FILE *rpt = fopen(loc, "w");
 	struct branch *b;
 	unsigned long lu;
 	struct recent_command *rc;
 
 	if (!rpt) {
-		error("can't write crash report %s: %s", loc, strerror(errno));
+		error_errno("can't write crash report %s", loc);
 		free(loc);
 		return;
 	}
 
 	fprintf(stderr, "fast-import: dumping crash report to %s\n", loc);
 
