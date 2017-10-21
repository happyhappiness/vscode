 	char *name;
 };
 
 static struct idlist *uidlist;
 static struct idlist *gidlist;
 
-static struct idlist *add_list(int id, char *name)
+static struct idlist *add_to_list(struct idlist **root, int id, char *name,
+				  int id2)
 {
-	struct idlist *list = new(struct idlist);
-	if (!list) out_of_memory("add_list");
-	list->next = NULL;
-	list->name = strdup(name);
-	if (!list->name) out_of_memory("add_list");
-	list->id = (int)id;
-	return list;
+	struct idlist *node = new(struct idlist);
+	if (!node)
+		out_of_memory("add_to_list");
+	node->next = *root;
+	node->name = name;
+	node->id = id;
+	node->id2 = id2;
+	*root = node;
+	return node;
 }
 
-
-
 /* turn a uid into a user name */
 static char *uid_to_name(uid_t uid)
 {
 	struct passwd *pass = getpwuid(uid);
-	if (pass) return(pass->pw_name);
+	if (pass)
+		return strdup(pass->pw_name);
 	return NULL;
 }
 
 /* turn a gid into a group name */
 static char *gid_to_name(gid_t gid)
 {
 	struct group *grp = getgrgid(gid);
-	if (grp) return(grp->gr_name);
+	if (grp)
+		return strdup(grp->gr_name);
 	return NULL;
 }
 
 static int map_uid(int id, char *name)
 {
 	uid_t uid;
-	if (name_to_uid(name, &uid) && uid != 0)
+	if (uid != 0 && name_to_uid(name, &uid))
 		return uid;
 	return id;
 }
 
 static int map_gid(int id, char *name)
 {
 	gid_t gid;
-	if (name_to_gid(name, &gid) && gid != 0)
+	if (gid != 0 && name_to_gid(name, &gid))
 		return gid;
 	return id;
 }
 
+static int is_in_group(gid_t gid)
+{
+#ifdef HAVE_GETGROUPS
+	static gid_t last_in = GID_NONE, last_out;
+	static int ngroups = -2;
+	static GETGROUPS_T *gidset;
+	int n;
+
+	if (gid == last_in)
+		return last_out;
+	if (ngroups < -1) {
+		gid_t mygid = MY_GID();
+		if ((ngroups = getgroups(0, NULL)) < 0)
+			ngroups = 0;
+		gidset = new_array(GETGROUPS_T, ngroups+1);
+		if (!gidset)
+			out_of_memory("is_in_group");
+		if (ngroups > 0)
+			ngroups = getgroups(ngroups, gidset);
+		/* The default gid might not be in the list on some systems. */
+		for (n = 0; n < ngroups; n++) {
+			if (gidset[n] == mygid)
+				break;
+		}
+		if (n == ngroups)
+			gidset[ngroups++] = mygid;
+		if (verbose > 3) {
+			int pos;
+			char *gidbuf = new_array(char, ngroups*21+32);
+			if (!gidbuf)
+				out_of_memory("is_in_group");
+			sprintf(gidbuf, "process has %d gid%s: ",
+			    ngroups, ngroups == 1? "" : "s");
+			pos = strlen(gidbuf);
+			for (n = 0; n < ngroups; n++) {
+				sprintf(gidbuf+pos, " %d", (int)gidset[n]);
+				pos += strlen(gidbuf+pos);
+			}
+			rprintf(FINFO, "%s\n", gidbuf);
+			free(gidbuf);
+		}
+	}
+
+	last_in = gid;
+	for (n = 0; n < ngroups; n++) {
+		if (gidset[n] == gid)
+			return last_out = 1;
+	}
+	return last_out = 0;
+
+#else
+	static gid_t mygid = GID_NONE;
+	if (mygid == GID_NONE) {
+		mygid = MY_GID();
+		if (verbose > 3)
+			rprintf(FINFO, "process has gid %d\n", (int)mygid);
+	}
+	return gid == mygid;
+#endif
+}
+
+/* Add a uid to the list of uids.  Only called on receiving side. */
+static struct idlist *recv_add_uid(int id, char *name)
+{
+	int id2 = name ? map_uid(id, name) : id;
+	struct idlist *node;
+
+	node = add_to_list(&uidlist, id, name, map_uid(id, name));
+
+	if (verbose > 3) {
+		rprintf(FINFO, "uid %d(%s) maps to %d\n",
+		    id, name ? name : "", id2);
+	}
+
+	return node;
+}
+
+/* Add a gid to the list of gids.  Only called on receiving side. */
+static struct idlist *recv_add_gid(int id, char *name)
+{
+	int id2 = name ? map_gid(id, name) : id;
+	struct idlist *node;
+
+	if (!am_root && !is_in_group(id2))
+		id2 = GID_NONE;
+	node = add_to_list(&gidlist, id, name, id2);
+
+	if (verbose > 3) {
+		rprintf(FINFO, "gid %d(%s) maps to %d\n",
+		    id, name ? name : "", id2);
+	}
+
+	return node;
+}
+
 /* this function is a definate candidate for a faster algorithm */
 static uid_t match_uid(uid_t uid)
 {
 	static uid_t last_in, last_out;
-	struct idlist *list = uidlist;
+	struct idlist *list;
 
-	if (uid == last_in) return last_out;
+	if (uid == 0)
+		return 0;
+
+	if (uid == last_in)
+		return last_out;
 
 	last_in = uid;
 
-	while (list) {
-		if (list->id == (int)uid) {
-			last_out = (uid_t)list->id2;
-			return last_out;
-		}
-		list = list->next;
+	for (list = uidlist; list; list = list->next) {
+		if (list->id == (int)uid)
+			return last_out = (uid_t)list->id2;
 	}
-	
-	last_out = uid;
-	return last_out;
+
+	return last_out = uid;
 }
 
 static gid_t match_gid(gid_t gid)
 {
-	static gid_t last_in, last_out;
-	struct idlist *list = gidlist;
+	static gid_t last_in = GID_NONE, last_out = GID_NONE;
+	struct idlist *list;
 
-	if (gid == last_in) return last_out;
+	if (gid == GID_NONE)
+		return GID_NONE;
+
+	if (gid == last_in)
+		return last_out;
 
 	last_in = gid;
 
-	while (list) {
-		if (list->id == (int)gid) {
-			last_out = (gid_t)list->id2;
-			return last_out;
-		}
-		list = list->next;
+	for (list = gidlist; list; list = list->next) {
+		if (list->id == (int)gid)
+			return last_out = (gid_t)list->id2;
 	}
-	
-	if (am_root)
-		last_out = gid;
-	else
-		last_out = (gid_t) -1;
-	return last_out;
+
+	list = recv_add_gid(gid, NULL);
+	return last_out = list->id2;
 }
 
-/* add a uid to the list of uids */
+/* Add a uid to the list of uids.  Only called on sending side. */
 void add_uid(uid_t uid)
 {
-	struct idlist *list = uidlist;
-	char *name;
-
-	if (numeric_ids) return;
-
-	/* don't map root */
-	if (uid==0) return;
+	struct idlist *list;
 
-	if (!list) {
-		if (!(name = uid_to_name(uid))) return;
-		uidlist = add_list((int)uid, name);
+	if (uid == 0)	/* don't map root */
 		return;
-	}
 
-	while (list->next) {
-		if (list->id == (int)uid) return;
-		list = list->next;
+	for (list = uidlist; list; list = list->next) {
+		if (list->id == (int)uid)
+			return;
 	}
 
-	if (list->id == (int)uid) return;
-
-	if (!(name = uid_to_name(uid))) return;
-
-	list->next = add_list((int)uid, name);
+	add_to_list(&uidlist, (int)uid, uid_to_name(uid), 0);
 }
 
-/* add a gid to the list of gids */
+/* Add a gid to the list of gids.  Only called on sending side. */
 void add_gid(gid_t gid)
 {
-	struct idlist *list = gidlist;
-	char *name;
-
-	if (numeric_ids) return;
-
-	/* don't map root */
-	if (gid==0) return;
+	struct idlist *list;
 
-	if (!list) {
-		if (!(name = gid_to_name(gid))) return;
-		gidlist = add_list((int)gid, name);
+	if (gid == 0)	/* don't map root */
 		return;
-	}
 
-	while (list->next) {
-		if (list->id == (int)gid) return;
-		list = list->next;
+	for (list = gidlist; list; list = list->next) {
+		if (list->id == (int)gid)
+			return;
 	}
 
-	if (list->id == (int)gid) return;
-
-	if (!(name = gid_to_name(gid))) return;
-
-	list->next = add_list((int)gid, name);
+	add_to_list(&gidlist, (int)gid, gid_to_name(gid), 0);
 }
 
 
 /* send a complete uid/gid mapping to the peer */
 void send_uid_list(int f)
 {
 	struct idlist *list;
 
-	if (numeric_ids) return;
+	if (numeric_ids)
+		return;
 
 	if (preserve_uid) {
+		int len;
 		/* we send sequences of uid/byte-length/name */
-		list = uidlist;
-		while (list) {
-			int len = strlen(list->name);
+		for (list = uidlist; list; list = list->next) {
+			if (!list->name)
+				continue;
+			len = strlen(list->name);
 			write_int(f, list->id);
 			write_byte(f, len);
 			write_buf(f, list->name, len);
-			list = list->next;
 		}
 
 		/* terminate the uid list with a 0 uid. We explicitly exclude
-		   0 from the list */
+		 * 0 from the list */
 		write_int(f, 0);
 	}
 
 	if (preserve_gid) {
-		list = gidlist;
-		while (list) {
-			int len = strlen(list->name);
+		int len;
+		for (list = gidlist; list; list = list->next) {
+			if (!list->name)
+				continue;
+			len = strlen(list->name);
 			write_int(f, list->id);
 			write_byte(f, len);
 			write_buf(f, list->name, len);
-			list = list->next;
 		}
 		write_int(f, 0);
 	}
 }
 
 /* recv a complete uid/gid mapping from the peer and map the uid/gid
-   in the file list to local names */
+ * in the file list to local names */
 void recv_uid_list(int f, struct file_list *flist)
 {
 	int id, i;
 	char *name;
-	struct idlist *list;
-
-	if (numeric_ids) return;
 
-	if (preserve_uid) {
+	if (preserve_uid && !numeric_ids) {
 		/* read the uid list */
-		list = uidlist;
-		id = read_int(f);
-		while (id != 0) {
+		while ((id = read_int(f)) != 0) {
 			int len = read_byte(f);
 			name = new_array(char, len+1);
-			if (!name) out_of_memory("recv_uid_list");
+			if (!name)
+				out_of_memory("recv_uid_list");
 			read_sbuf(f, name, len);
-			if (!list) {
-				uidlist = add_list(id, name);
-				list = uidlist;
-			} else {
-				list->next = add_list(id, name);
-				list = list->next;
-			}
-			list->id2 = map_uid(id, name);
-			free(name);
-			id = read_int(f);
+			recv_add_uid(id, name); /* node keeps name's memory */
 		}
 	}
 
 
-	if (preserve_gid) {
-		/* and the gid list */
-		list = gidlist;
-		id = read_int(f);
-		while (id != 0) {
+	if (preserve_gid && !numeric_ids) {
+		/* read the gid list */
+		while ((id = read_int(f)) != 0) {
 			int len = read_byte(f);
 			name = new_array(char, len+1);
-			if (!name) out_of_memory("recv_uid_list");
+			if (!name)
+				out_of_memory("recv_uid_list");
 			read_sbuf(f, name, len);
-			if (!list) {
-				gidlist = add_list(id, name);
-				list = gidlist;
-			} else {
-				list->next = add_list(id, name);
-				list = list->next;
-			}
-			list->id2 = map_gid(id, name);
-			free(name);
-			id = read_int(f);
+			recv_add_gid(id, name); /* node keeps name's memory */
 		}
 	}
 
-	if (!(am_root && preserve_uid) && !preserve_gid) return;
-
 	/* now convert the uid/gid of all files in the list to the mapped
-	   uid/gid */
-	for (i=0;i<flist->count;i++) {
-		if (am_root && preserve_uid && flist->files[i]->uid != 0) {
+	 * uid/gid */
+	if (am_root && preserve_uid && !numeric_ids) {
+		for (i = 0; i < flist->count; i++)
 			flist->files[i]->uid = match_uid(flist->files[i]->uid);
-		}
-		if (preserve_gid && flist->files[i]->gid != 0) {
+	}
+	if (preserve_gid && (!am_root || !numeric_ids)) {
+		for (i = 0; i < flist->count; i++)
 			flist->files[i]->gid = match_gid(flist->files[i]->gid);
-		}
 	}
 }
