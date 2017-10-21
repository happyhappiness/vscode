 			send_msg_int(MSG_SUCCESS, ndx);
 	}
 
 	if (inc_recurse) {
 		int gnum = F_HL_GNUM(file);
 		struct ht_int32_node *node = hashtable_find(prior_hlinks, gnum, 0);
-		assert(node != NULL && node->data != NULL);
-		assert(CVAL(node->data, 0) == 0);
+		if (node == NULL) {
+			rprintf(FERROR, "Unable to find a hlink node for %d (%s)\n", gnum, f_name(file, prev_name));
+			exit_cleanup(RERR_MESSAGEIO);
+		}
+		if (node->data == NULL) {
+			rprintf(FERROR, "Hlink node data for %d is NULL (%s)\n", gnum, f_name(file, prev_name));
+			exit_cleanup(RERR_MESSAGEIO);
+		}
+		if (CVAL(node->data, 0) != 0) {
+			rprintf(FERROR, "Hlink node data for %d already has path=%s (%s)\n",
+				gnum, (char*)node->data, f_name(file, prev_name));
+			exit_cleanup(RERR_MESSAGEIO);
+		}
 		free(node->data);
 		if (!(node->data = strdup(our_name)))
 			out_of_memory("finish_hard_link");
 	}
 }
 
