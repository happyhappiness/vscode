 }
 
 void parse_commit_or_die(struct commit *item)
 {
 	if (parse_commit(item))
 		die("unable to parse commit %s",
-		    item ? sha1_to_hex(item->object.sha1) : "(null)");
+		    item ? oid_to_hex(&item->object.oid) : "(null)");
 }
 
 int find_commit_subject(const char *commit_buffer, const char **subject)
 {
 	const char *eol;
 	const char *p = commit_buffer;
