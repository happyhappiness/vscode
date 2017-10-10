 		}
 
 		target = resolve_refdup(name,
 					RESOLVE_REF_READING
 					| RESOLVE_REF_NO_RECURSE
 					| RESOLVE_REF_ALLOW_BAD_NAME,
-					sha1, &flags);
+					oid.hash, &flags);
 		if (!target) {
 			error(remote_branch
 			      ? _("remote-tracking branch '%s' not found.")
 			      : _("branch '%s' not found."), bname.buf);
 			ret = 1;
 			continue;
 		}
 
 		if (!(flags & (REF_ISSYMREF|REF_ISBROKEN)) &&
-		    check_branch_commit(bname.buf, name, sha1, head_rev, kinds,
+		    check_branch_commit(bname.buf, name, &oid, head_rev, kinds,
 					force)) {
 			ret = 1;
 			goto next;
 		}
 
-		if (delete_ref(name, is_null_sha1(sha1) ? NULL : sha1,
+		if (delete_ref(NULL, name, is_null_oid(&oid) ? NULL : oid.hash,
 			       REF_NODEREF)) {
 			error(remote_branch
 			      ? _("Error deleting remote-tracking branch '%s'")
 			      : _("Error deleting branch '%s'"),
 			      bname.buf);
 			ret = 1;
