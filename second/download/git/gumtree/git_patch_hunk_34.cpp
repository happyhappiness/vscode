 		add_extra_header(&buffer, extra);
 		extra = extra->next;
 	}
 	strbuf_addch(&buffer, '\n');
 
 	/* And add the comment */
-	strbuf_addbuf(&buffer, msg);
+	strbuf_add(&buffer, msg, msg_len);
 
 	/* And check the encoding */
 	if (encoding_is_utf8 && !verify_utf8(&buffer))
 		fprintf(stderr, commit_utf8_warn);
 
 	if (sign_commit && do_sign_commit(&buffer, sign_commit))
