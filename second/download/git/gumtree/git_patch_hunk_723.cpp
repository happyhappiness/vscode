 			}
 			/* skip "objects\n" at end */
 			if (okay) {
 				struct strbuf target = STRBUF_INIT;
 				strbuf_add(&target, base, serverlen);
 				strbuf_add(&target, data + i, posn - i - 7);
-				warning("adding alternate object store: %s",
-					target.buf);
-				newalt = xmalloc(sizeof(*newalt));
-				newalt->next = NULL;
-				newalt->base = strbuf_detach(&target, NULL);
-				newalt->got_indices = 0;
-				newalt->packs = NULL;
-
-				while (tail->next != NULL)
-					tail = tail->next;
-				tail->next = newalt;
+
+				if (is_alternate_allowed(target.buf)) {
+					warning("adding alternate object store: %s",
+						target.buf);
+					newalt = xmalloc(sizeof(*newalt));
+					newalt->next = NULL;
+					newalt->base = strbuf_detach(&target, NULL);
+					newalt->got_indices = 0;
+					newalt->packs = NULL;
+
+					while (tail->next != NULL)
+						tail = tail->next;
+					tail->next = newalt;
+				}
 			}
 		}
 		i = posn + 1;
 	}
 
 	cdata->got_alternates = 1;
