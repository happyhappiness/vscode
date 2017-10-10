 			}
 			/* skip "objects\n" at end */
 			if (okay) {
 				struct strbuf target = STRBUF_INIT;
 				strbuf_add(&target, base, serverlen);
 				strbuf_add(&target, data + i, posn - i - 7);
-				if (walker->get_verbosely)
-					fprintf(stderr, "Also look at %s\n",
-						target.buf);
+				warning("adding alternate object store: %s",
+					target.buf);
 				newalt = xmalloc(sizeof(*newalt));
 				newalt->next = NULL;
 				newalt->base = strbuf_detach(&target, NULL);
 				newalt->got_indices = 0;
 				newalt->packs = NULL;
 
