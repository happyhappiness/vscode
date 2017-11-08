static int want_found_object(int exclude, struct packed_git *p)
{
	if (exclude)
		return 1;
	if (incremental)
		return 0;

	/*
	 * When asked to do --local (do not include an object that appears in a
	 * pack we borrow from elsewhere) or --honor-pack-keep (do not include
	 * an object that appears in a pack marked with .keep), finding a pack
	 * that matches the criteria is sufficient for us to decide to omit it.
	 * However, even if this pack does not satisfy the criteria, we need to
	 * make sure no copy of this object appears in _any_ pack that makes us
	 * to omit the object, so we need to check all the packs.
	 *
	 * We can however first check whether these options can possible matter;
	 * if they do not matter we know we want the object in generated pack.
	 * Otherwise, we signal "-1" at the end to tell the caller that we do
	 * not know either way, and it needs to check more packs.
	 */
	if (!ignore_packed_keep &&
	    (!local || !have_non_local_packs))
		return 1;

	if (local && !p->pack_local)
		return 0;
	if (ignore_packed_keep && p->pack_local && p->pack_keep)
		return 0;

	/* we don't know yet; keep looking for more packs */
	return -1;
}