 /*
  * Porcelain/Incremental format wants to show a lot of details per
  * commit.  Instead of repeating this every line, emit it only once,
  * the first time each commit appears in the output (unless the
  * user has specifically asked for us to repeat).
  */
-static int emit_one_suspect_detail(struct origin *suspect, int repeat)
+static int emit_one_suspect_detail(struct blame_origin *suspect, int repeat)
 {
 	struct commit_info ci;
 
 	if (!repeat && (suspect->commit->object.flags & METAINFO_SHOWN))
 		return 0;
 
 	suspect->commit->object.flags |= METAINFO_SHOWN;
 	get_commit_info(suspect->commit, &ci, 1);
 	printf("author %s\n", ci.author.buf);
 	printf("author-mail %s\n", ci.author_mail.buf);
-	printf("author-time %lu\n", ci.author_time);
+	printf("author-time %"PRItime"\n", ci.author_time);
 	printf("author-tz %s\n", ci.author_tz.buf);
 	printf("committer %s\n", ci.committer.buf);
 	printf("committer-mail %s\n", ci.committer_mail.buf);
-	printf("committer-time %lu\n", ci.committer_time);
+	printf("committer-time %"PRItime"\n", ci.committer_time);
 	printf("committer-tz %s\n", ci.committer_tz.buf);
 	printf("summary %s\n", ci.summary.buf);
 	if (suspect->commit->object.flags & UNINTERESTING)
 		printf("boundary\n");
 
 	commit_info_destroy(&ci);
