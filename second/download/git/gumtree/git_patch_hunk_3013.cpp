 		if (args->dry_run || push_cert_nonce)
 			continue;
 
 		if (check_to_send_update(ref, args) < 0)
 			continue;
 
-		old_hex = sha1_to_hex(ref->old_sha1);
-		new_hex = sha1_to_hex(ref->new_sha1);
+		old_hex = oid_to_hex(&ref->old_oid);
+		new_hex = oid_to_hex(&ref->new_oid);
 		if (!cmds_sent) {
 			packet_buf_write(&req_buf,
 					 "%s %s %s%c%s",
 					 old_hex, new_hex, ref->name, 0,
 					 cap_buf.buf);
 			cmds_sent = 1;
