		pack_open_windows--;
		p->windows = w->next;
		free(w);
	}
}

/*
 * The LRU pack is the one with the oldest MRU window, preferring packs
 * with no used windows, or the oldest mtime if it has no windows allocated.
 */
static void find_lru_pack(struct packed_git *p, struct packed_git **lru_p, struct pack_window **mru_w, int *accept_windows_inuse)
{
