(le = cpio->links_head; le; le = le->next) {
		if (le->dev == dev && le->ino == ino) {
			archive_entry_copy_hardlink(entry, le->name);

			if (--le->links <= 0) {
				if (le->previous != NULL)
					le->previous->next = le->next;
				if (le->next != NULL)
					le->next->previous = le->previous;
				if (cpio->links_head == le)
					cpio->links_head = le->next;
				free(le->name);
				free(le);
			}

			return (ARCHIVE_OK);
		}
	}