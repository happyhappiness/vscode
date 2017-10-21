 	if (preserve_uid) {
 		/* read the uid list */
 		list = uidlist;
 		id = read_int(f);
 		while (id != 0) {
 			int len = read_byte(f);
-			name = (char *)malloc(len);
+			name = (char *)malloc(len+1);
 			if (!name) out_of_memory("recv_uid_list");
-			read_buf(f, name, len);
+			read_sbuf(f, name, len);
 			if (!list) {
 				uidlist = add_list(id, name);
 				list = uidlist;
 			} else {
 				list->next = add_list(id, name);
 				list = list->next;
