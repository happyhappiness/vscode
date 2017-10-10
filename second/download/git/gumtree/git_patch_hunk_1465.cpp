 		ret = -1;
 	}
 	free(url);
 	return ret;
 }
 
-static void fetch_symref(const char *path, char **symref, unsigned char *sha1)
+static void fetch_symref(const char *path, char **symref, struct object_id *oid)
 {
 	char *url = xstrfmt("%s%s", repo->url, path);
 	struct strbuf buffer = STRBUF_INIT;
 	const char *name;
 
 	if (http_get_strbuf(url, &buffer, NULL) != HTTP_OK)
 		die("Couldn't get %s for remote symref\n%s", url,
 		    curl_errorstr);
 	free(url);
 
-	free(*symref);
-	*symref = NULL;
-	hashclr(sha1);
+	FREE_AND_NULL(*symref);
+	oidclr(oid);
 
 	if (buffer.len == 0)
 		return;
 
 	/* Cut off trailing newline. */
 	strbuf_rtrim(&buffer);
 
 	/* If it's a symref, set the refname; otherwise try for a sha1 */
 	if (skip_prefix(buffer.buf, "ref: ", &name)) {
 		*symref = xmemdupz(name, buffer.len - (name - buffer.buf));
 	} else {
-		get_sha1_hex(buffer.buf, sha1);
+		get_oid_hex(buffer.buf, oid);
 	}
 
 	strbuf_release(&buffer);
 }
 
-static int verify_merge_base(unsigned char *head_sha1, struct ref *remote)
+static int verify_merge_base(struct object_id *head_oid, struct ref *remote)
 {
-	struct commit *head = lookup_commit_or_die(head_sha1, "HEAD");
-	struct commit *branch = lookup_commit_or_die(remote->old_oid.hash, remote->name);
+	struct commit *head = lookup_commit_or_die(head_oid, "HEAD");
+	struct commit *branch = lookup_commit_or_die(&remote->old_oid,
+						     remote->name);
 
 	return in_merge_bases(branch, head);
 }
 
 static int delete_remote_branch(const char *pattern, int force)
 {
 	struct ref *refs = remote_refs;
 	struct ref *remote_ref = NULL;
-	unsigned char head_sha1[20];
+	struct object_id head_oid;
 	char *symref = NULL;
 	int match;
 	int patlen = strlen(pattern);
 	int i;
 	struct active_request_slot *slot;
 	struct slot_results results;
