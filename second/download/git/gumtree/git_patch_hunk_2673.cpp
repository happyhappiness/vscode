 			char *end;
 			opts->depth = strtol(value, &end, 0);
 			if (*end)
 				die("transport: invalid depth option '%s'", value);
 		}
 		return 0;
-	} else if (!strcmp(name, TRANS_OPT_PUSH_CERT)) {
-		opts->push_cert = !!value;
-		return 0;
 	}
 	return 1;
 }
 
 static int connect_setup(struct transport *transport, int for_push, int verbose)
 {
