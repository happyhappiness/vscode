 	}
 
 	/* Special cases that add new entry. */
 	if ((!oldurl && !delete_mode) || add_mode) {
 		if (add_mode)
 			git_config_set_multivar(name_buf.buf, newurl,
-				"^$", 0);
+						       "^$", 0);
 		else
 			git_config_set(name_buf.buf, newurl);
 		strbuf_release(&name_buf);
+
 		return 0;
 	}
 
 	/* Old URL specified. Demand that one matches. */
 	if (regcomp(&old_regex, oldurl, REG_EXTENDED))
 		die(_("Invalid old URL pattern: %s"), oldurl);
