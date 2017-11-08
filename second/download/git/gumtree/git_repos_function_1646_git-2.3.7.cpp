int is_pack_valid(struct packed_git *p)
{
	/* An already open pack is known to be valid. */
	if (p->pack_fd != -1)
		return 1;

	/* If the pack has one window completely covering the
	 * file size, the pack is known to be valid even if
	 * the descriptor is not currently open.
	 */
	if (p->windows) {
		struct pack_window *w = p->windows;

		if (!w->offset && w->len == p->pack_size)
			return 1;
	}

	/* Force the pack to open to prove its valid. */
	return !open_packed_git(p);
}