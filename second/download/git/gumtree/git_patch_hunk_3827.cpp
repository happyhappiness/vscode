 		if (!value)
 			opts->depth = 0;
 		else {
 			char *end;
 			opts->depth = strtol(value, &end, 0);
 			if (*end)
-				die("transport: invalid depth option '%s'", value);
+				die(_("transport: invalid depth option '%s'"), value);
 		}
 		return 0;
 	}
 	return 1;
 }
 
