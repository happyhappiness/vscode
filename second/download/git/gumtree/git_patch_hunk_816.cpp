 		if (parse_feature_request(features, "no-progress"))
 			no_progress = 1;
 		if (parse_feature_request(features, "include-tag"))
 			use_include_tag = 1;
 
 		o = parse_object(sha1_buf);
-		if (!o)
+		if (!o) {
+			packet_write_fmt(1,
+					 "ERR upload-pack: not our ref %s",
+					 sha1_to_hex(sha1_buf));
 			die("git upload-pack: not our ref %s",
 			    sha1_to_hex(sha1_buf));
+		}
 		if (!(o->flags & WANTED)) {
 			o->flags |= WANTED;
 			if (!((allow_unadvertised_object_request & ALLOW_ANY_SHA1) == ALLOW_ANY_SHA1
 			      || is_our_ref(o)))
 				has_non_tip = 1;
 			add_object_array(o, NULL, &want_obj);
