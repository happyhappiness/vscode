 static int total_matches;
 
 extern struct stats stats;
 
 struct target {
 	tag t;
-	size_t i;
+	int32 i;
 };
 
 static struct target *targets;
 
-static size_t *tag_table;
+static int32 *tag_table;
 
 #define gettag2(s1,s2) (((s1) + (s2)) & 0xFFFF)
 #define gettag(sum) gettag2((sum)&0xFFFF,(sum)>>16)
 
 static int compare_targets(struct target *t1,struct target *t2)
 {
 	return (int)t1->t - (int)t2->t;
 }
 
 
 static void build_hash_table(struct sum_struct *s)
 {
-	size_t i;
+	int32 i;
 
 	if (!tag_table)
-		tag_table = new_array(size_t, TABLESIZE);
+		tag_table = new_array(int32, TABLESIZE);
 
 	targets = new_array(struct target, s->count);
 	if (!tag_table || !targets)
 		out_of_memory("build_hash_table");
 
 	for (i = 0; i < s->count; i++) {
