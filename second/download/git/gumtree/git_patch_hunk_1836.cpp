 				    slash < data + posn && colon < slash) {
 					okay = 1;
 				}
 			}
 			/* skip "objects\n" at end */
 			if (okay) {
-				target = xmalloc(serverlen + posn - i - 6);
-				memcpy(target, base, serverlen);
-				memcpy(target + serverlen, data + i,
-				       posn - i - 7);
-				target[serverlen + posn - i - 7] = 0;
+				struct strbuf target = STRBUF_INIT;
+				strbuf_add(&target, base, serverlen);
+				strbuf_add(&target, data + i, posn - i - 7);
 				if (walker->get_verbosely)
-					fprintf(stderr,
-						"Also look at %s\n", target);
+					fprintf(stderr, "Also look at %s\n",
+						target.buf);
 				newalt = xmalloc(sizeof(*newalt));
 				newalt->next = NULL;
-				newalt->base = target;
+				newalt->base = strbuf_detach(&target, NULL);
 				newalt->got_indices = 0;
 				newalt->packs = NULL;
 
 				while (tail->next != NULL)
 					tail = tail->next;
 				tail->next = newalt;
