 	char *free, *end;
 	unsigned pool_count;
 };
 
 static uint32_t *paint_alloc(struct paint_info *info)
 {
-	unsigned nr = (info->nr_bits + 31) / 32;
+	unsigned nr = DIV_ROUND_UP(info->nr_bits, 32);
 	unsigned size = nr * sizeof(uint32_t);
 	void *p;
 	if (!info->pool_count || size > info->end - info->free) {
 		if (size > POOL_SIZE)
 			die("BUG: pool size too small for %d in paint_alloc()",
 			    size);
