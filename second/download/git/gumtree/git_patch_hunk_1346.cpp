 		rp_error("hook declined to update %s", name);
 		return "hook declined";
 	}
 
 	if (is_null_oid(new_oid)) {
 		struct strbuf err = STRBUF_INIT;
-		if (!parse_object(old_oid->hash)) {
+		if (!parse_object(old_oid)) {
 			old_oid = NULL;
 			if (ref_exists(name)) {
 				rp_warning("Allowing deletion of corrupt ref.");
 			} else {
 				rp_warning("Deleting a non-existent ref.");
 				cmd->did_not_exist = 1;
