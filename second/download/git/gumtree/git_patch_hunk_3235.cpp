 	 * is good to deal with chains of trust, but
 	 * is not consistent with what deref_tag() does
 	 * which peels the onion to the core.
 	 */
 	buf = get_obj(tagged, &obj, &size, &eaten);
 	if (!buf)
-		die("missing object %s for %s",
+		die(_("missing object %s for %s"),
 		    sha1_to_hex(tagged), ref->refname);
 	if (!obj)
-		die("parse_object_buffer failed on %s for %s",
+		die(_("parse_object_buffer failed on %s for %s"),
 		    sha1_to_hex(tagged), ref->refname);
 	grab_values(ref->value, 1, obj, buf, size);
 	if (!eaten)
 		free(buf);
 }
 
