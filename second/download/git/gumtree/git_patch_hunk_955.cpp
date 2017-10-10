 		if (shallow_update && si->shallow_ref[cmd->index] &&
 		    update_shallow_ref(cmd, si))
 			return "shallow error";
 
 		if (ref_transaction_update(transaction,
 					   namespaced_name,
-					   new_sha1, old_sha1,
+					   new_oid->hash, old_oid->hash,
 					   0, "push",
 					   &err)) {
 			rp_error("%s", err.buf);
 			strbuf_release(&err);
 
 			return "failed to update ref";
