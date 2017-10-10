 	}
 
 	if (base->ref_first <= base->ref_last) {
 		struct object_entry *child = objects + deltas[base->ref_first].obj_no;
 		struct base_data *result = alloc_base_data();
 
-		assert(child->real_type == OBJ_REF_DELTA);
+		if (!compare_and_swap_type(&child->real_type, OBJ_REF_DELTA,
+					   base->obj->real_type))
+			die("BUG: child->real_type != OBJ_REF_DELTA");
+
 		resolve_delta(child, base, result);
 		if (base->ref_first == base->ref_last && base->ofs_last == -1)
 			free_base_data(base);
 
 		base->ref_first++;
 		return result;
