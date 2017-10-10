 		opt.diffopt.output_format = DIFF_FORMAT_RAW;
 
 	log_tree_commit(&opt, commit);
 }
 
 /*
+ * The terms used for this bisect session are stored in BISECT_TERMS.
+ * We read them and store them to adapt the messages accordingly.
+ * Default is bad/good.
+ */
+void read_bisect_terms(const char **read_bad, const char **read_good)
+{
+	struct strbuf str = STRBUF_INIT;
+	const char *filename = git_path("BISECT_TERMS");
+	FILE *fp = fopen(filename, "r");
+
+	if (!fp) {
+		if (errno == ENOENT) {
+			*read_bad = "bad";
+			*read_good = "good";
+			return;
+		} else {
+			die("could not read file '%s': %s", filename,
+				strerror(errno));
+		}
+	} else {
+		strbuf_getline(&str, fp, '\n');
+		*read_bad = strbuf_detach(&str, NULL);
+		strbuf_getline(&str, fp, '\n');
+		*read_good = strbuf_detach(&str, NULL);
+	}
+	strbuf_release(&str);
+	fclose(fp);
+}
+
+/*
  * We use the convention that exiting with an exit code 10 means that
  * the bisection process finished successfully.
  * In this case the calling shell script should exit 0.
  *
  * If no_checkout is non-zero, the bisection process does not
  * checkout the trial commit but instead simply updates BISECT_HEAD.
