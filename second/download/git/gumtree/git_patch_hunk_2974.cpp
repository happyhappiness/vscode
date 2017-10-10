 						  sha1, NULL);
 			if (!strcmp(ref->refname, head))
 				v->s = "*";
 			else
 				v->s = " ";
 			continue;
+		} else if (match_atom_name(name, "align", &valp)) {
+			struct align *align = &v->u.align;
+			struct strbuf **s, **to_free;
+			int width = -1;
+
+			if (!valp)
+				die(_("expected format: %%(align:<width>,<position>)"));
+
+			/*
+			 * TODO: Implement a function similar to strbuf_split_str()
+			 * which would omit the separator from the end of each value.
+			 */
+			s = to_free = strbuf_split_str(valp, ',', 0);
+
+			align->position = ALIGN_LEFT;
+
+			while (*s) {
+				/*  Strip trailing comma */
+				if (s[1])
+					strbuf_setlen(s[0], s[0]->len - 1);
+				if (!strtoul_ui(s[0]->buf, 10, (unsigned int *)&width))
+					;
+				else if (!strcmp(s[0]->buf, "left"))
+					align->position = ALIGN_LEFT;
+				else if (!strcmp(s[0]->buf, "right"))
+					align->position = ALIGN_RIGHT;
+				else if (!strcmp(s[0]->buf, "middle"))
+					align->position = ALIGN_MIDDLE;
+				else
+					die(_("improper format entered align:%s"), s[0]->buf);
+				s++;
+			}
+
+			if (width < 0)
+				die(_("positive width expected with the %%(align) atom"));
+			align->width = width;
+			strbuf_list_free(to_free);
+			v->handler = align_atom_handler;
+			continue;
+		} else if (!strcmp(name, "end")) {
+			v->handler = end_atom_handler;
+			continue;
 		} else
 			continue;
 
 		formatp = strchr(name, ':');
 		if (formatp) {
 			int num_ours, num_theirs;
