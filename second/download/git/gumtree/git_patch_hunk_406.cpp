 		printf("(missing)\n");
 	else if (ce == o->df_conflict_entry)
 		printf("(conflict)\n");
 	else
 		printf("%06o #%d %s %.8s\n",
 		       ce->ce_mode, ce_stage(ce), ce->name,
-		       sha1_to_hex(ce->sha1));
+		       oid_to_hex(&ce->oid));
 }
 
 static int debug_merge(const struct cache_entry * const *stages,
 		       struct unpack_trees_options *o)
 {
 	int i;
