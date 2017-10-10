 	if (type < 0)
 		die(_("object %s not found"), oid_to_hex(&ref->new_oid));
 
 	if (!oidcmp(&ref->old_oid, &ref->new_oid)) {
 		if (verbosity > 0)
 			format_display(display, '=', _("[up to date]"), NULL,
-				       remote, pretty_ref);
+				       remote, pretty_ref, summary_width);
 		return 0;
 	}
 
 	if (current_branch &&
 	    !strcmp(ref->name, current_branch->name) &&
 	    !(update_head_ok || is_bare_repository()) &&
