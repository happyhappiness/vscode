 	for (ref = remote_refs; ref; ref = ref->next) {
 		char *old_hex, *new_hex;
 
 		if (args->dry_run || args->push_cert)
 			continue;
 
-		if (!ref_update_to_be_sent(ref, args))
+		if (check_to_send_update(ref, args) < 0)
 			continue;
 
 		old_hex = sha1_to_hex(ref->old_sha1);
 		new_hex = sha1_to_hex(ref->new_sha1);
 		if (!cmds_sent) {
 			packet_buf_write(&req_buf,
