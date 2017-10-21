 	static GETGROUPS_T *gidset;
 	int n;
 
 	if (gid == last_in && last_out >= 0)
 		return last_out;
 	if (ngroups < -1) {
-		gid_t mygid = MY_GID();
 		if ((ngroups = getgroups(0, NULL)) < 0)
 			ngroups = 0;
 		gidset = new_array(GETGROUPS_T, ngroups+1);
 		if (!gidset)
 			out_of_memory("is_in_group");
 		if (ngroups > 0)
 			ngroups = getgroups(ngroups, gidset);
 		/* The default gid might not be in the list on some systems. */
 		for (n = 0; n < ngroups; n++) {
-			if (gidset[n] == mygid)
+			if (gidset[n] == our_gid)
 				break;
 		}
 		if (n == ngroups)
-			gidset[ngroups++] = mygid;
-		if (verbose > 3) {
+			gidset[ngroups++] = our_gid;
+		if (DEBUG_GTE(OWN, 2)) {
 			int pos;
 			char *gidbuf = new_array(char, ngroups*21+32);
 			if (!gidbuf)
 				out_of_memory("is_in_group");
 			pos = snprintf(gidbuf, 32, "process has %d gid%s: ",
 				       ngroups, ngroups == 1? "" : "s");
