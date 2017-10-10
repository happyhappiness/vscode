 	}
 }
 
 static void parse_options_check(const struct option *opts)
 {
 	int err = 0;
+	char short_opts[128];
 
+	memset(short_opts, '\0', sizeof(short_opts));
 	for (; opts->type != OPTION_END; opts++) {
 		if ((opts->flags & PARSE_OPT_LASTARG_DEFAULT) &&
 		    (opts->flags & PARSE_OPT_OPTARG))
 			err |= optbug(opts, "uses incompatible flags "
 					"LASTARG_DEFAULT and OPTARG");
+		if (opts->short_name) {
+			if (0x7F <= opts->short_name)
+				err |= optbug(opts, "invalid short name");
+			else if (short_opts[opts->short_name]++)
+				err |= optbug(opts, "short name already used");
+		}
 		if (opts->flags & PARSE_OPT_NODASH &&
 		    ((opts->flags & PARSE_OPT_OPTARG) ||
 		     !(opts->flags & PARSE_OPT_NOARG) ||
 		     !(opts->flags & PARSE_OPT_NONEG) ||
 		     opts->long_name))
 			err |= optbug(opts, "uses feature "
