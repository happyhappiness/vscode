 				  " yourself if you want to.\n"
 				  "An empty message aborts the commit.\n"), comment_line_char);
 		if (only_include_assumed)
 			status_printf_ln(s, GIT_COLOR_NORMAL,
 					"%s", only_include_assumed);
 
-		ai_tmp = cut_ident_timestamp_part(author_ident->buf);
-		ci_tmp = cut_ident_timestamp_part(committer_ident.buf);
-		if (strcmp(author_ident->buf, committer_ident.buf))
+		split_ident_or_die(&ai, author_ident);
+		split_ident_or_die(&ci, &committer_ident);
+
+		if (ident_cmp(&ai, &ci))
 			status_printf_ln(s, GIT_COLOR_NORMAL,
 				_("%s"
-				"Author:    %s"),
+				"Author:    %.*s <%.*s>"),
 				ident_shown++ ? "" : "\n",
-				author_ident->buf);
+				(int)(ai.name_end - ai.name_begin), ai.name_begin,
+				(int)(ai.mail_end - ai.mail_begin), ai.mail_begin);
+
+		if (author_date_is_interesting())
+			status_printf_ln(s, GIT_COLOR_NORMAL,
+				_("%s"
+				"Date:      %s"),
+				ident_shown++ ? "" : "\n",
+				show_ident_date(&ai, DATE_NORMAL));
 
 		if (!committer_ident_sufficiently_given())
 			status_printf_ln(s, GIT_COLOR_NORMAL,
 				_("%s"
-				"Committer: %s"),
+				"Committer: %.*s <%.*s>"),
 				ident_shown++ ? "" : "\n",
-				committer_ident.buf);
+				(int)(ci.name_end - ci.name_begin), ci.name_begin,
+				(int)(ci.mail_end - ci.mail_begin), ci.mail_begin);
 
 		if (ident_shown)
-			status_printf_ln(s, GIT_COLOR_NORMAL, "");
+			status_printf_ln(s, GIT_COLOR_NORMAL, "%s", "");
 
 		saved_color_setting = s->use_color;
 		s->use_color = 0;
 		commitable = run_status(s->fp, index_file, prefix, 1, s);
 		s->use_color = saved_color_setting;
-
-		*ai_tmp = ' ';
-		*ci_tmp = ' ';
 	} else {
 		unsigned char sha1[20];
 		const char *parent = "HEAD";
 
 		if (!active_nr && read_cache() < 0)
 			die(_("Cannot read index"));
