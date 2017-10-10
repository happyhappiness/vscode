 	if (cmdmode == 'v')
 		return for_each_tag_name(argv, verify_tag);
 
 	if (msg.given || msgfile) {
 		if (msg.given && msgfile)
 			die(_("only one -F or -m option is allowed."));
-		annotate = 1;
 		if (msg.given)
 			strbuf_addbuf(&buf, &(msg.buf));
 		else {
 			if (!strcmp(msgfile, "-")) {
 				if (strbuf_read(&buf, 0, 1024) < 0)
 					die_errno(_("cannot read '%s'"), msgfile);
