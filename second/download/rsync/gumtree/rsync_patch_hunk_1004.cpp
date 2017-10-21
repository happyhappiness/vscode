 		out_of_memory("recv_user_name");
 	read_sbuf(f, name, len);
 	if (numeric_ids < 0) {
 		free(name);
 		name = NULL;
 	}
-	node = recv_add_uid(uid, name); /* node keeps name's memory */
+	node = recv_add_id(&uidlist, uidmap, uid, name); /* node keeps name's memory */
 	return node->id2;
 }
 
 gid_t recv_group_name(int f, gid_t gid, uint16 *flags_ptr)
 {
 	struct idlist *node;
