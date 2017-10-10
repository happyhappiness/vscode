 			char *end;
 			opts->depth = strtol(value, &end, 0);
 			if (*end)
 				die(_("transport: invalid depth option '%s'"), value);
 		}
 		return 0;
+	} else if (!strcmp(name, TRANS_OPT_DEEPEN_SINCE)) {
+		opts->deepen_since = value;
+		return 0;
+	} else if (!strcmp(name, TRANS_OPT_DEEPEN_NOT)) {
+		opts->deepen_not = (const struct string_list *)value;
+		return 0;
+	} else if (!strcmp(name, TRANS_OPT_DEEPEN_RELATIVE)) {
+		opts->deepen_relative = !!value;
+		return 0;
 	}
 	return 1;
 }
 
 static int connect_setup(struct transport *transport, int for_push)
 {
