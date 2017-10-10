 
 		saved_color_setting = s->use_color;
 		s->use_color = 0;
 		commitable = run_status(s->fp, index_file, prefix, 1, s);
 		s->use_color = saved_color_setting;
 	} else {
-		unsigned char sha1[20];
+		struct object_id oid;
 		const char *parent = "HEAD";
 
 		if (!active_nr && read_cache() < 0)
 			die(_("Cannot read index"));
 
 		if (amend)
 			parent = "HEAD^1";
 
-		if (get_sha1(parent, sha1)) {
+		if (get_sha1(parent, oid.hash)) {
 			int i, ita_nr = 0;
 
 			for (i = 0; i < active_nr; i++)
 				if (ce_intent_to_add(active_cache[i]))
 					ita_nr++;
 			commitable = active_nr - ita_nr > 0;
