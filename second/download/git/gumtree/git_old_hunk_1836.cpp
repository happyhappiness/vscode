				    slash < data + posn && colon < slash) {
					okay = 1;
				}
			}
			/* skip "objects\n" at end */
			if (okay) {
				target = xmalloc(serverlen + posn - i - 6);
				memcpy(target, base, serverlen);
				memcpy(target + serverlen, data + i,
				       posn - i - 7);
				target[serverlen + posn - i - 7] = 0;
				if (walker->get_verbosely)
					fprintf(stderr,
						"Also look at %s\n", target);
				newalt = xmalloc(sizeof(*newalt));
				newalt->next = NULL;
				newalt->base = target;
				newalt->got_indices = 0;
				newalt->packs = NULL;

				while (tail->next != NULL)
					tail = tail->next;
				tail->next = newalt;
