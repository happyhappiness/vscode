 		if (len < 4*4 || len != (size_t)cnt*(4+4) + 4*4) {
 			free(buf);
 			return -1;
 		}
 
 		racl->user_obj = IVAL(buf, 0);
+		if (racl->user_obj == NO_ENTRY)
+			racl->user_obj = (mode >> 6) & 7;
 		racl->group_obj = IVAL(buf, 4);
+		if (racl->group_obj == NO_ENTRY)
+			racl->group_obj = (mode >> 3) & 7;
 		racl->mask_obj = IVAL(buf, 8);
 		racl->other_obj = IVAL(buf, 12);
+		if (racl->other_obj == NO_ENTRY)
+			racl->other_obj = mode & 7;
 
 		if (cnt) {
 			char *bp = buf + 4*4;
 			id_access *ida;
 			if (!(ida = racl->names.idas = new_array(id_access, cnt)))
 				out_of_memory("get_rsync_acl");
