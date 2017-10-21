 		} else {
 #ifdef HAVE_GETGROUPLIST
 			int j;
 			/* See if authorizing user is a real user, and if so, see
 			 * if it is in a group that matches tok+1 wildmat. */
 			if (auth_uid_groups_cnt < 0) {
-				gid_t gid_list[64];
+				item_list gid_list = EMPTY_ITEM_LIST;
 				uid_t auth_uid;
-				auth_uid_groups_cnt = sizeof gid_list / sizeof (gid_t);
 				if (!user_to_uid(line, &auth_uid, False)
-				 || getallgroups(auth_uid, gid_list, &auth_uid_groups_cnt) != NULL)
+				 || getallgroups(auth_uid, &gid_list) != NULL)
 					auth_uid_groups_cnt = 0;
 				else {
+					gid_t *gid_array = gid_list.items;
+					auth_uid_groups_cnt = gid_list.count;
 					if ((auth_uid_groups = new_array(char *, auth_uid_groups_cnt)) == NULL)
 						out_of_memory("auth_server");
 					for (j = 0; j < auth_uid_groups_cnt; j++)
-						auth_uid_groups[j] = gid_to_group(gid_list[j]);
+						auth_uid_groups[j] = gid_to_group(gid_array[j]);
 				}
 			}
 			for (j = 0; j < auth_uid_groups_cnt; j++) {
 				if (auth_uid_groups[j] && wildmatch(tok+1, auth_uid_groups[j])) {
 					group_match = j;
 					break;
