 		unsigned char from_obj[20], to_obj[20];
 		struct strbuf **split;
 		int err;
 
 		split = strbuf_split(&buf, ' ');
 		if (!split[0] || !split[1])
-			die(_("Malformed input line: '%s'."), buf.buf);
+			die(_("malformed input line: '%s'."), buf.buf);
 		strbuf_rtrim(split[0]);
 		strbuf_rtrim(split[1]);
 		if (get_sha1(split[0]->buf, from_obj))
-			die(_("Failed to resolve '%s' as a valid ref."), split[0]->buf);
+			die(_("failed to resolve '%s' as a valid ref."), split[0]->buf);
 		if (get_sha1(split[1]->buf, to_obj))
-			die(_("Failed to resolve '%s' as a valid ref."), split[1]->buf);
+			die(_("failed to resolve '%s' as a valid ref."), split[1]->buf);
 
 		if (rewrite_cmd)
 			err = copy_note_for_rewrite(c, from_obj, to_obj);
 		else
 			err = copy_note(t, from_obj, to_obj, force,
 					combine_notes_overwrite);
 
 		if (err) {
-			error(_("Failed to copy notes from '%s' to '%s'"),
+			error(_("failed to copy notes from '%s' to '%s'"),
 			      split[0]->buf, split[1]->buf);
 			ret = 1;
 		}
 
 		strbuf_list_free(split);
 	}
