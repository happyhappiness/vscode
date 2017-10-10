 			type = oe->type;
 	} else
 		die("Invalid ref name or SHA1 expression: %s", from);
 	read_next_command();
 
 	/* tagger ... */
-	if (starts_with(command_buf.buf, "tagger ")) {
-		tagger = parse_ident(command_buf.buf + 7);
+	if (skip_prefix(command_buf.buf, "tagger ", &v)) {
+		tagger = parse_ident(v);
 		read_next_command();
 	} else
 		tagger = NULL;
 
 	/* tag payload/message */
 	parse_data(&msg, 0, NULL);
