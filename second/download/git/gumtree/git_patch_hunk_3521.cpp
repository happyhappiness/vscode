 
 		/*
 		 * CE_INTENT_TO_ADD entries exist on on-disk index but
 		 * they are not part of generated trees. Invalidate up
 		 * to root to force cache-tree users to read elsewhere.
 		 */
-		if (ce_intent_to_add(ce)) {
+		if (!sub && ce_intent_to_add(ce)) {
 			to_invalidate = 1;
 			continue;
 		}
 
+		/*
+		 * "sub" can be an empty tree if all subentries are i-t-a.
+		 */
+		if (contains_ita && !hashcmp(sha1, EMPTY_TREE_SHA1_BIN))
+			continue;
+
 		strbuf_grow(&buffer, entlen + 100);
 		strbuf_addf(&buffer, "%o %.*s%c", mode, entlen, path + baselen, '\0');
 		strbuf_add(&buffer, sha1, 20);
 
 #if DEBUG
 		fprintf(stderr, "cache-tree update-one %o %.*s\n",
