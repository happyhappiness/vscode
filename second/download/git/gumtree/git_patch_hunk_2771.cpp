 	assert(!state->author_date);
 	state->author_date = strbuf_detach(&sb, NULL);
 
 	assert(!state->msg);
 	msg = strstr(buffer, "\n\n");
 	if (!msg)
-		die(_("unable to parse commit %s"), sha1_to_hex(commit->object.sha1));
+		die(_("unable to parse commit %s"), oid_to_hex(&commit->object.oid));
 	state->msg = xstrdup(msg + 2);
 	state->msg_len = strlen(state->msg);
 }
 
 /**
  * Writes `commit` as a patch to the state directory's "patch" file.
