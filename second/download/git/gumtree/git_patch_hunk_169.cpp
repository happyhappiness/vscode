 static volatile sig_atomic_t checkpoint_requested;
 
 /* Where to write output of cat-blob commands */
 static int cat_blob_fd = STDOUT_FILENO;
 
 static void parse_argv(void);
-static void parse_cat_blob(void);
-static void parse_ls(struct branch *b);
+static void parse_cat_blob(const char *p);
+static void parse_ls(const char *p, struct branch *b);
 
 static void write_branch_report(FILE *rpt, struct branch *b)
 {
 	fprintf(rpt, "%s:\n", b->name);
 
 	fprintf(rpt, "  status      :");
