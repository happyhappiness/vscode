 #include "cache.h"
+#include "config.h"
 #include "commit.h"
 #include "refs.h"
 #include "notes-utils.h"
 
 void create_notes_commit(struct notes_tree *t, struct commit_list *parents,
 			 const char *msg, size_t msg_len,
 			 unsigned char *result_sha1)
 {
-	unsigned char tree_sha1[20];
+	struct object_id tree_oid;
 
 	assert(t->initialized);
 
-	if (write_notes_tree(t, tree_sha1))
+	if (write_notes_tree(t, tree_oid.hash))
 		die("Failed to write notes tree to database");
 
 	if (!parents) {
 		/* Deduce parent commit from t->ref */
-		unsigned char parent_sha1[20];
-		if (!read_ref(t->ref, parent_sha1)) {
-			struct commit *parent = lookup_commit(parent_sha1);
+		struct object_id parent_oid;
+		if (!read_ref(t->ref, parent_oid.hash)) {
+			struct commit *parent = lookup_commit(&parent_oid);
 			if (parse_commit(parent))
 				die("Failed to find/parse commit %s", t->ref);
 			commit_list_insert(parent, &parents);
 		}
 		/* else: t->ref points to nothing, assume root/orphan commit */
 	}
 
-	if (commit_tree(msg, msg_len, tree_sha1, parents, result_sha1, NULL, NULL))
+	if (commit_tree(msg, msg_len, tree_oid.hash, parents, result_sha1, NULL, NULL))
 		die("Failed to commit notes tree to database");
 }
 
 void commit_notes(struct notes_tree *t, const char *msg)
 {
 	struct strbuf buf = STRBUF_INIT;
-	unsigned char commit_sha1[20];
+	struct object_id commit_oid;
 
 	if (!t)
 		t = &default_notes_tree;
 	if (!t->initialized || !t->update_ref || !*t->update_ref)
 		die(_("Cannot commit uninitialized/unreferenced notes tree"));
 	if (!t->dirty)
 		return; /* don't have to commit an unchanged tree */
 
 	/* Prepare commit message and reflog message */
 	strbuf_addstr(&buf, msg);
 	strbuf_complete_line(&buf);
 
-	create_notes_commit(t, NULL, buf.buf, buf.len, commit_sha1);
+	create_notes_commit(t, NULL, buf.buf, buf.len, commit_oid.hash);
 	strbuf_insert(&buf, 0, "notes: ", 7); /* commit message starts at index 7 */
-	update_ref(buf.buf, t->update_ref, commit_sha1, NULL, 0,
+	update_ref(buf.buf, t->update_ref, commit_oid.hash, NULL, 0,
 		   UPDATE_REFS_DIE_ON_ERR);
 
 	strbuf_release(&buf);
 }
 
 int parse_notes_merge_strategy(const char *v, enum notes_merge_strategy *s)
