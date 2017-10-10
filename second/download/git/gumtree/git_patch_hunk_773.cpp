  */
 static int add_rejected_path(struct unpack_trees_options *o,
 			     enum unpack_trees_error_types e,
 			     const char *path)
 {
 	if (!o->show_all_errors)
-		return error(ERRORMSG(o, e), path);
+		return error(ERRORMSG(o, e), super_prefixed(path));
 
 	/*
 	 * Otherwise, insert in a list for future display by
 	 * display_error_msgs()
 	 */
 	string_list_append(&o->unpack_rejects[e], path);
