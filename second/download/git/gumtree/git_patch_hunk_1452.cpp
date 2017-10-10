 			 */
 			if (!args->stateless_rpc && count == INITIAL_FLUSH)
 				continue;
 
 			consume_shallow_list(args, fd[0]);
 			do {
-				ack = get_ack(fd[0], result_sha1);
+				ack = get_ack(fd[0], result_oid);
 				if (ack)
 					print_verbose(args, _("got %s %d %s"), "ack",
-						      ack, sha1_to_hex(result_sha1));
+						      ack, oid_to_hex(result_oid));
 				switch (ack) {
 				case ACK:
 					flushes = 0;
 					multi_ack = 0;
 					retval = 0;
 					goto done;
 				case ACK_common:
 				case ACK_ready:
 				case ACK_continue: {
 					struct commit *commit =
-						lookup_commit(result_sha1);
+						lookup_commit(result_oid);
 					if (!commit)
-						die(_("invalid commit %s"), sha1_to_hex(result_sha1));
+						die(_("invalid commit %s"), oid_to_hex(result_oid));
 					if (args->stateless_rpc
 					 && ack == ACK_common
 					 && !(commit->object.flags & COMMON)) {
 						/* We need to replay the have for this object
 						 * on the next RPC request so the peer knows
 						 * it is in common with us.
 						 */
-						const char *hex = sha1_to_hex(result_sha1);
+						const char *hex = oid_to_hex(result_oid);
 						packet_buf_write(&req_buf, "have %s\n", hex);
 						state_len = req_buf.len;
 						/*
 						 * Reset in_vain because an ack
 						 * for this commit has not been
 						 * seen.
