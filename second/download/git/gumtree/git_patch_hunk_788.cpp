 int bisect_next_all(const char *prefix, int no_checkout)
 {
 	struct rev_info revs;
 	struct commit_list *tried;
 	int reaches = 0, all = 0, nr, steps;
 	const unsigned char *bisect_rev;
-	char steps_msg[32];
+	char *steps_msg;
 
 	read_bisect_terms(&term_bad, &term_good);
 	if (read_bisect_refs())
 		die(_("reading bisect refs failed"));
 
 	check_good_are_ancestors_of_bad(prefix, no_checkout);
