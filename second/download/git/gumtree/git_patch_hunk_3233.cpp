 				v->s = "";
 			else {
 				*cp = '\0';
 				v->s = xstrdup(buf + 1);
 			}
 			continue;
-		} else if (!deref && grab_objectname(name, ref->objectname, v)) {
+		} else if (!deref && grab_objectname(name, ref->objectname, v, atom)) {
 			continue;
 		} else if (!strcmp(name, "HEAD")) {
 			const char *head;
 			unsigned char sha1[20];
 
 			head = resolve_ref_unsafe("HEAD", RESOLVE_REF_READING,
 						  sha1, NULL);
 			if (!strcmp(ref->refname, head))
 				v->s = "*";
 			else
 				v->s = " ";
 			continue;
-		} else if (match_atom_name(name, "align", &valp)) {
-			struct align *align = &v->u.align;
-			struct strbuf **s, **to_free;
-			int width = -1;
-
-			if (!valp)
-				die(_("expected format: %%(align:<width>,<position>)"));
-
-			/*
-			 * TODO: Implement a function similar to strbuf_split_str()
-			 * which would omit the separator from the end of each value.
-			 */
-			s = to_free = strbuf_split_str(valp, ',', 0);
-
-			align->position = ALIGN_LEFT;
-
-			while (*s) {
-				/*  Strip trailing comma */
-				if (s[1])
-					strbuf_setlen(s[0], s[0]->len - 1);
-				if (!strtoul_ui(s[0]->buf, 10, (unsigned int *)&width))
-					;
-				else if (!strcmp(s[0]->buf, "left"))
-					align->position = ALIGN_LEFT;
-				else if (!strcmp(s[0]->buf, "right"))
-					align->position = ALIGN_RIGHT;
-				else if (!strcmp(s[0]->buf, "middle"))
-					align->position = ALIGN_MIDDLE;
-				else
-					die(_("improper format entered align:%s"), s[0]->buf);
-				s++;
-			}
-
-			if (width < 0)
-				die(_("positive width expected with the %%(align) atom"));
-			align->width = width;
-			strbuf_list_free(to_free);
+		} else if (starts_with(name, "align")) {
+			v->u.align = atom->u.align;
 			v->handler = align_atom_handler;
 			continue;
 		} else if (!strcmp(name, "end")) {
 			v->handler = end_atom_handler;
 			continue;
 		} else
 			continue;
 
 		formatp = strchr(name, ':');
 		if (formatp) {
-			int num_ours, num_theirs;
 			const char *arg;
 
 			formatp++;
 			if (!strcmp(formatp, "short"))
 				refname = shorten_unambiguous_ref(refname,
 						      warn_ambiguous_refs);
 			else if (skip_prefix(formatp, "strip=", &arg))
 				refname = strip_ref_components(refname, arg);
-			else if (!strcmp(formatp, "track") &&
-				 (starts_with(name, "upstream") ||
-				  starts_with(name, "push"))) {
-
-				if (stat_tracking_info(branch, &num_ours,
-						       &num_theirs, NULL))
-					continue;
-
-				if (!num_ours && !num_theirs)
-					v->s = "";
-				else if (!num_ours)
-					v->s = xstrfmt("[behind %d]", num_theirs);
-				else if (!num_theirs)
-					v->s = xstrfmt("[ahead %d]", num_ours);
-				else
-					v->s = xstrfmt("[ahead %d, behind %d]",
-						       num_ours, num_theirs);
-				continue;
-			} else if (!strcmp(formatp, "trackshort") &&
-				   (starts_with(name, "upstream") ||
-				    starts_with(name, "push"))) {
-				assert(branch);
-
-				if (stat_tracking_info(branch, &num_ours,
-							&num_theirs, NULL))
-					continue;
-
-				if (!num_ours && !num_theirs)
-					v->s = "=";
-				else if (!num_ours)
-					v->s = "<";
-				else if (!num_theirs)
-					v->s = ">";
-				else
-					v->s = "<>";
-				continue;
-			} else
-				die("unknown %.*s format %s",
+			else
+				die(_("unknown %.*s format %s"),
 				    (int)(formatp - name), name, formatp);
 		}
 
 		if (!deref)
 			v->s = refname;
 		else
