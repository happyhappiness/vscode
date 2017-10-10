 #include "tree.h"
 #include "commit.h"
 #include "tag.h"
 
 #define BLOCKING 1024
 
-#define DEFINE_ALLOCATOR(name, type)				\
-static unsigned int name##_allocs;				\
-void *alloc_##name##_node(void)					\
-{								\
-	static int nr;						\
-	static type *block;					\
-	void *ret;						\
-								\
-	if (!nr) {						\
-		nr = BLOCKING;					\
-		block = xmalloc(BLOCKING * sizeof(type));	\
-	}							\
-	nr--;							\
-	name##_allocs++;					\
-	ret = block++;						\
-	memset(ret, 0, sizeof(type));				\
-	return ret;						\
-}
-
 union any_object {
 	struct object object;
 	struct blob blob;
 	struct tree tree;
 	struct commit commit;
 	struct tag tag;
 };
 
-DEFINE_ALLOCATOR(blob, struct blob)
-DEFINE_ALLOCATOR(tree, struct tree)
-DEFINE_ALLOCATOR(raw_commit, struct commit)
-DEFINE_ALLOCATOR(tag, struct tag)
-DEFINE_ALLOCATOR(object, union any_object)
+struct alloc_state {
+	int count; /* total number of nodes allocated */
+	int nr;    /* number of nodes left in current allocation */
+	void *p;   /* first free node in current allocation */
+};
+
+static inline void *alloc_node(struct alloc_state *s, size_t node_size)
+{
+	void *ret;
+
+	if (!s->nr) {
+		s->nr = BLOCKING;
+		s->p = xmalloc(BLOCKING * node_size);
+	}
+	s->nr--;
+	s->count++;
+	ret = s->p;
+	s->p = (char *)s->p + node_size;
+	memset(ret, 0, node_size);
+	return ret;
+}
+
+static struct alloc_state blob_state;
+void *alloc_blob_node(void)
+{
+	struct blob *b = alloc_node(&blob_state, sizeof(struct blob));
+	b->object.type = OBJ_BLOB;
+	return b;
+}
+
+static struct alloc_state tree_state;
+void *alloc_tree_node(void)
+{
+	struct tree *t = alloc_node(&tree_state, sizeof(struct tree));
+	t->object.type = OBJ_TREE;
+	return t;
+}
+
+static struct alloc_state tag_state;
+void *alloc_tag_node(void)
+{
+	struct tag *t = alloc_node(&tag_state, sizeof(struct tag));
+	t->object.type = OBJ_TAG;
+	return t;
+}
+
+static struct alloc_state object_state;
+void *alloc_object_node(void)
+{
+	struct object *obj = alloc_node(&object_state, sizeof(union any_object));
+	obj->type = OBJ_NONE;
+	return obj;
+}
+
+static struct alloc_state commit_state;
+
+unsigned int alloc_commit_index(void)
+{
+	static unsigned int count;
+	return count++;
+}
 
 void *alloc_commit_node(void)
 {
-	static int commit_count;
-	struct commit *c = alloc_raw_commit_node();
-	c->index = commit_count++;
+	struct commit *c = alloc_node(&commit_state, sizeof(struct commit));
+	c->object.type = OBJ_COMMIT;
+	c->index = alloc_commit_index();
 	return c;
 }
 
 static void report(const char *name, unsigned int count, size_t size)
 {
 	fprintf(stderr, "%10s: %8u (%"PRIuMAX" kB)\n",
 			name, count, (uintmax_t) size);
 }
 
 #define REPORT(name, type)	\
-    report(#name, name##_allocs, name##_allocs * sizeof(type) >> 10)
+    report(#name, name##_state.count, name##_state.count * sizeof(type) >> 10)
 
 void alloc_report(void)
 {
 	REPORT(blob, struct blob);
 	REPORT(tree, struct tree);
-	REPORT(raw_commit, struct commit);
+	REPORT(commit, struct commit);
 	REPORT(tag, struct tag);
 	REPORT(object, union any_object);
 }
