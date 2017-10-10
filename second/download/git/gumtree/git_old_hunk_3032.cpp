				(cmp = strcmp(buffer + 41,
				      (*list)->next->name)) > 0)
			list = &(*list)->next;
		if (!(*list)->next || cmp < 0) {
			struct ref *next = alloc_ref(buffer + 41);
			buffer[40] = '\0';
			if (get_sha1_hex(buffer, next->old_sha1)) {
				warning ("invalid SHA-1: %s", buffer);
				free(next);
				continue;
			}
			next->next = (*list)->next;
			(*list)->next = next;
