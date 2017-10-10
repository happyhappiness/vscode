 		case DENY_UNCONFIGURED:
 			rp_error("refusing to update checked out branch: %s", name);
 			if (deny_current_branch == DENY_UNCONFIGURED)
 				refuse_unconfigured_deny();
 			return "branch is currently checked out";
 		case DENY_UPDATE_INSTEAD:
-			ret = update_worktree(new_sha1);
+			ret = update_worktree(new_oid->hash);
 			if (ret)
 				return ret;
 			break;
 		}
 	}
 
-	if (!is_null_sha1(new_sha1) && !has_sha1_file(new_sha1)) {
+	if (!is_null_oid(new_oid) && !has_object_file(new_oid)) {
 		error("unpack should have generated %s, "
-		      "but I can't find it!", sha1_to_hex(new_sha1));
+		      "but I can't find it!", oid_to_hex(new_oid));
 		return "bad pack";
 	}
 
-	if (!is_null_sha1(old_sha1) && is_null_sha1(new_sha1)) {
+	if (!is_null_oid(old_oid) && is_null_oid(new_oid)) {
 		if (deny_deletes && starts_with(name, "refs/heads/")) {
 			rp_error("denying ref deletion for %s", name);
 			return "deletion prohibited";
 		}
 
 		if (head_name && !strcmp(namespaced_name, head_name)) {
