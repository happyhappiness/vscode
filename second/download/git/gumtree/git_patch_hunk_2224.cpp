 }
 
 static struct base_data *find_unresolved_deltas_1(struct base_data *base,
 						  struct base_data *prev_base)
 {
 	if (base->ref_last == -1 && base->ofs_last == -1) {
-		union delta_base base_spec;
-
-		hashcpy(base_spec.sha1, base->obj->idx.sha1);
-		find_delta_children(&base_spec,
-				    &base->ref_first, &base->ref_last, OBJ_REF_DELTA);
-
-		memset(&base_spec, 0, sizeof(base_spec));
-		base_spec.offset = base->obj->idx.offset;
-		find_delta_children(&base_spec,
-				    &base->ofs_first, &base->ofs_last, OBJ_OFS_DELTA);
+		find_ref_delta_children(base->obj->idx.sha1,
+					&base->ref_first, &base->ref_last,
+					OBJ_REF_DELTA);
+
+		find_ofs_delta_children(base->obj->idx.offset,
+					&base->ofs_first, &base->ofs_last,
+					OBJ_OFS_DELTA);
 
 		if (base->ref_last == -1 && base->ofs_last == -1) {
 			free(base->data);
 			return NULL;
 		}
 
 		link_base_data(prev_base, base);
 	}
 
 	if (base->ref_first <= base->ref_last) {
-		struct object_entry *child = objects + deltas[base->ref_first].obj_no;
+		struct object_entry *child = objects + ref_deltas[base->ref_first].obj_no;
 		struct base_data *result = alloc_base_data();
 
 		if (!compare_and_swap_type(&child->real_type, OBJ_REF_DELTA,
 					   base->obj->real_type))
 			die("BUG: child->real_type != OBJ_REF_DELTA");
 
