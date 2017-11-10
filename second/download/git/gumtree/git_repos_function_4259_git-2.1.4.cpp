static int preimage_sha1_in_gitlink_patch(struct patch *p, unsigned char sha1[20])
{
	/*
	 * A usable gitlink patch has only one fragment (hunk) that looks like:
	 * @@ -1 +1 @@
	 * -Subproject commit <old sha1>
	 * +Subproject commit <new sha1>
	 * or
	 * @@ -1 +0,0 @@
	 * -Subproject commit <old sha1>
	 * for a removal patch.
	 */
	struct fragment *hunk = p->fragments;
	static const char heading[] = "-Subproject commit ";
	char *preimage;

	if (/* does the patch have only one hunk? */
	    hunk && !hunk->next &&
	    /* is its preimage one line? */
	    hunk->oldpos == 1 && hunk->oldlines == 1 &&
	    /* does preimage begin with the heading? */
	    (preimage = memchr(hunk->patch, '\n', hunk->size)) != NULL &&
	    starts_with(++preimage, heading) &&
	    /* does it record full SHA-1? */
	    !get_sha1_hex(preimage + sizeof(heading) - 1, sha1) &&
	    preimage[sizeof(heading) + 40 - 1] == '\n' &&
	    /* does the abbreviated name on the index line agree with it? */
	    starts_with(preimage + sizeof(heading) - 1, p->old_sha1_prefix))
		return 0; /* it all looks fine */

	/* we may have full object name on the index line */
	return get_sha1_hex(p->old_sha1_prefix, sha1);
}