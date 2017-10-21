 
 	module_id = i;
 
 	if (lp_read_only(i))
 		read_only = 1;
 
-	p = lp_uid(i);
-	if (!name_to_uid(p, &uid)) {
-		if (!isdigit(*p)) {
-			rprintf(FERROR,"Invalid uid %s\n", p);
-			io_printf(fd,"@ERROR: invalid uid\n");
-			return -1;
-		} 
-		uid = atoi(p);
-	}
+	am_root = (getuid() == 0);
 
-	p = lp_gid(i);
-	if (!name_to_gid(p, &gid)) {
-		if (!isdigit(*p)) {
-			rprintf(FERROR,"Invalid gid %s\n", p);
-			io_printf(fd,"@ERROR: invalid gid\n");
-			return -1;
-		} 
-		gid = atoi(p);
+	if (am_root) {
+		p = lp_uid(i);
+		if (!name_to_uid(p, &uid)) {
+			if (!isdigit(*p)) {
+				rprintf(FERROR,"Invalid uid %s\n", p);
+				io_printf(fd,"@ERROR: invalid uid\n");
+				return -1;
+			} 
+			uid = atoi(p);
+		}
+
+		p = lp_gid(i);
+		if (!name_to_gid(p, &gid)) {
+			if (!isdigit(*p)) {
+				rprintf(FERROR,"Invalid gid %s\n", p);
+				io_printf(fd,"@ERROR: invalid gid\n");
+				return -1;
+			} 
+			gid = atoi(p);
+		}
 	}
 
 	p = lp_include_from(i);
 	add_exclude_file(p, 1, 1);
 
 	p = lp_include(i);
