 #include "diff.h"
 #include "commit.h"
 #include "sha1-lookup.h"
 #include "patch-ids.h"
 
 int commit_patch_id(struct commit *commit, struct diff_options *options,
-		    unsigned char *sha1)
+		    unsigned char *sha1, int diff_header_only)
 {
 	if (commit->parents)
 		diff_tree_sha1(commit->parents->item->object.oid.hash,
 			       commit->object.oid.hash, "", options);
 	else
 		diff_root_tree_sha1(commit->object.oid.hash, "", options);
 	diffcore_std(options);
-	return diff_flush_patch_id(options, sha1);
+	return diff_flush_patch_id(options, sha1, diff_header_only);
 }
 
-static const unsigned char *patch_id_access(size_t index, void *table)
-{
-	struct patch_id **id_table = table;
-	return id_table[index]->patch_id;
-}
-
-static int patch_pos(struct patch_id **table, int nr, const unsigned char *id)
-{
-	return sha1_pos(id, table, nr, patch_id_access);
+/*
+ * When we cannot load the full patch-id for both commits for whatever
+ * reason, the function returns -1 (i.e. return error(...)). Despite
+ * the "cmp" in the name of this function, the caller only cares about
+ * the return value being zero (a and b are equivalent) or non-zero (a
+ * and b are different), and returning non-zero would keep both in the
+ * result, even if they actually were equivalent, in order to err on
+ * the side of safety.  The actual value being negative does not have
+ * any significance; only that it is non-zero matters.
+ */
+static int patch_id_cmp(struct patch_id *a,
+			struct patch_id *b,
+			struct diff_options *opt)
+{
+	if (is_null_sha1(a->patch_id) &&
+	    commit_patch_id(a->commit, opt, a->patch_id, 0))
+		return error("Could not get patch ID for %s",
+			oid_to_hex(&a->commit->object.oid));
+	if (is_null_sha1(b->patch_id) &&
+	    commit_patch_id(b->commit, opt, b->patch_id, 0))
+		return error("Could not get patch ID for %s",
+			oid_to_hex(&b->commit->object.oid));
+	return hashcmp(a->patch_id, b->patch_id);
 }
 
-#define BUCKET_SIZE 190 /* 190 * 21 = 3990, with slop close enough to 4K */
-struct patch_id_bucket {
-	struct patch_id_bucket *next;
-	int nr;
-	struct patch_id bucket[BUCKET_SIZE];
-};
-
 int init_patch_ids(struct patch_ids *ids)
 {
 	memset(ids, 0, sizeof(*ids));
 	diff_setup(&ids->diffopts);
 	DIFF_OPT_SET(&ids->diffopts, RECURSIVE);
 	diff_setup_done(&ids->diffopts);
+	hashmap_init(&ids->patches, (hashmap_cmp_fn)patch_id_cmp, 256);
 	return 0;
 }
 
 int free_patch_ids(struct patch_ids *ids)
 {
-	struct patch_id_bucket *next, *patches;
-
-	free(ids->table);
-	for (patches = ids->patches; patches; patches = next) {
-		next = patches->next;
-		free(patches);
-	}
+	hashmap_free(&ids->patches, 1);
 	return 0;
 }
 
-static struct patch_id *add_commit(struct commit *commit,
-				   struct patch_ids *ids,
-				   int no_add)
-{
-	struct patch_id_bucket *bucket;
-	struct patch_id *ent;
-	unsigned char sha1[20];
-	int pos;
-
-	if (commit_patch_id(commit, &ids->diffopts, sha1))
-		return NULL;
-	pos = patch_pos(ids->table, ids->nr, sha1);
-	if (0 <= pos)
-		return ids->table[pos];
-	if (no_add)
-		return NULL;
-
-	pos = -1 - pos;
+static int init_patch_id_entry(struct patch_id *patch,
+			       struct commit *commit,
+			       struct patch_ids *ids)
+{
+	unsigned char header_only_patch_id[GIT_SHA1_RAWSZ];
 
-	bucket = ids->patches;
-	if (!bucket || (BUCKET_SIZE <= bucket->nr)) {
-		bucket = xcalloc(1, sizeof(*bucket));
-		bucket->next = ids->patches;
-		ids->patches = bucket;
-	}
-	ent = &bucket->bucket[bucket->nr++];
-	hashcpy(ent->patch_id, sha1);
+	patch->commit = commit;
+	if (commit_patch_id(commit, &ids->diffopts, header_only_patch_id, 1))
+		return -1;
 
-	ALLOC_GROW(ids->table, ids->nr + 1, ids->alloc);
-	if (pos < ids->nr)
-		memmove(ids->table + pos + 1, ids->table + pos,
-			sizeof(ent) * (ids->nr - pos));
-	ids->nr++;
-	ids->table[pos] = ent;
-	return ids->table[pos];
+	hashmap_entry_init(patch, sha1hash(header_only_patch_id));
+	return 0;
 }
 
 struct patch_id *has_commit_patch_id(struct commit *commit,
 				     struct patch_ids *ids)
 {
-	return add_commit(commit, ids, 1);
+	struct patch_id patch;
+
+	memset(&patch, 0, sizeof(patch));
+	if (init_patch_id_entry(&patch, commit, ids))
+		return NULL;
+
+	return hashmap_get(&ids->patches, &patch, &ids->diffopts);
 }
 
 struct patch_id *add_commit_patch_id(struct commit *commit,
 				     struct patch_ids *ids)
 {
-	return add_commit(commit, ids, 0);
+	struct patch_id *key = xcalloc(1, sizeof(*key));
+
+	if (init_patch_id_entry(key, commit, ids)) {
+		free(key);
+		return NULL;
+	}
+
+	hashmap_add(&ids->patches, key);
+	return key;
 }
