 		assert(CVAL(node->data, 0) == 0);
 		free(node->data);
 		if (!(node->data = strdup(our_name)))
 			out_of_memory("finish_hard_link");
 	}
 }
+
+int skip_hard_link(struct file_struct *file, struct file_list **flist_p)
+{
+	struct file_list *flist;
+	int prev_ndx;
+
+	file->flags |= FLAG_SKIP_HLINK;
+	if (!(file->flags & FLAG_HLINK_LAST))
+		return -1;
+
+	check_prior(file, F_HL_GNUM(file), &prev_ndx, &flist);
+	if (prev_ndx >= 0) {
+		file = flist->files[prev_ndx - flist->ndx_start];
+		if (file->flags & (FLAG_HLINK_DONE|FLAG_FILE_SENT))
+			return -1;
+		file->flags |= FLAG_HLINK_LAST;
+		*flist_p = flist;
+	}
+
+	return prev_ndx;
+}
 #endif
