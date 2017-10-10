 		return is_shallow;
 	}
 	stat_validity_update(&shallow_stat, fileno(fp));
 	is_shallow = 1;
 
 	while (fgets(buf, sizeof(buf), fp)) {
-		unsigned char sha1[20];
-		if (get_sha1_hex(buf, sha1))
+		struct object_id oid;
+		if (get_oid_hex(buf, &oid))
 			die("bad shallow line: %s", buf);
-		register_shallow(sha1);
+		register_shallow(&oid);
 	}
 	fclose(fp);
 	return is_shallow;
 }
 
 struct commit_list *get_shallow_commits(struct object_array *heads, int depth,
