 
 	if (strcmp(var, "transfer.unpacklimit") == 0) {
 		transfer_unpack_limit = git_config_int(var, value);
 		return 0;
 	}
 
+	if (strcmp(var, "receive.fsck.skiplist") == 0) {
+		const char *path;
+
+		if (git_config_pathname(&path, var, value))
+			return 1;
+		strbuf_addf(&fsck_msg_types, "%cskiplist=%s",
+			fsck_msg_types.len ? ',' : '=', path);
+		free((char *)path);
+		return 0;
+	}
+
+	if (skip_prefix(var, "receive.fsck.", &var)) {
+		if (is_valid_msg_type(var, value))
+			strbuf_addf(&fsck_msg_types, "%c%s=%s",
+				fsck_msg_types.len ? ',' : '=', var, value);
+		else
+			warning("Skipping unknown msg id '%s'", var);
+		return 0;
+	}
+
 	if (strcmp(var, "receive.fsckobjects") == 0) {
 		receive_fsck_objects = git_config_bool(var, value);
 		return 0;
 	}
 
 	if (strcmp(var, "transfer.fsckobjects") == 0) {
