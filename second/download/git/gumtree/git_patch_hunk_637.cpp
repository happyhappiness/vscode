 	}
 	info->nr_theirs = dst;
 }
 
 define_commit_slab(ref_bitmap, uint32_t *);
 
+#define POOL_SIZE (512 * 1024)
+
 struct paint_info {
 	struct ref_bitmap ref_bitmap;
 	unsigned nr_bits;
-	char **slab;
+	char **pools;
 	char *free, *end;
-	unsigned slab_count;
+	unsigned pool_count;
 };
 
 static uint32_t *paint_alloc(struct paint_info *info)
 {
 	unsigned nr = (info->nr_bits + 31) / 32;
 	unsigned size = nr * sizeof(uint32_t);
 	void *p;
-	if (!info->slab_count || info->free + size > info->end) {
-		info->slab_count++;
-		REALLOC_ARRAY(info->slab, info->slab_count);
-		info->free = xmalloc(COMMIT_SLAB_SIZE);
-		info->slab[info->slab_count - 1] = info->free;
-		info->end = info->free + COMMIT_SLAB_SIZE;
+	if (!info->pool_count || size > info->end - info->free) {
+		if (size > POOL_SIZE)
+			die("BUG: pool size too small for %d in paint_alloc()",
+			    size);
+		info->pool_count++;
+		REALLOC_ARRAY(info->pools, info->pool_count);
+		info->free = xmalloc(POOL_SIZE);
+		info->pools[info->pool_count - 1] = info->free;
+		info->end = info->free + POOL_SIZE;
 	}
 	p = info->free;
 	info->free += size;
 	return p;
 }
 
 /*
  * Given a commit SHA-1, walk down to parents until either SEEN,
  * UNINTERESTING or BOTTOM is hit. Set the id-th bit in ref_bitmap for
  * all walked commits.
  */
 static void paint_down(struct paint_info *info, const unsigned char *sha1,
-		       int id)
+		       unsigned int id)
 {
 	unsigned int i, nr;
 	struct commit_list *head = NULL;
 	int bitmap_nr = (info->nr_bits + 31) / 32;
 	size_t bitmap_size = st_mult(sizeof(uint32_t), bitmap_nr);
 	uint32_t *tmp = xmalloc(bitmap_size); /* to be freed before return */
 	uint32_t *bitmap = paint_alloc(info);
 	struct commit *c = lookup_commit_reference_gently(sha1, 1);
 	if (!c)
 		return;
 	memset(bitmap, 0, bitmap_size);
-	bitmap[id / 32] |= (1 << (id % 32));
+	bitmap[id / 32] |= (1U << (id % 32));
 	commit_list_insert(c, &head);
 	while (head) {
 		struct commit_list *p;
 		struct commit *c = pop_commit(&head);
 		uint32_t **refs = ref_bitmap_at(&info->ref_bitmap, c);
 
