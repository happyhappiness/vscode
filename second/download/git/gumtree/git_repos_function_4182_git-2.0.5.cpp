static int write_out_one_reject(struct patch *patch)
{
	FILE *rej;
	char namebuf[PATH_MAX];
	struct fragment *frag;
	int cnt = 0;
	struct strbuf sb = STRBUF_INIT;

	for (cnt = 0, frag = patch->fragments; frag; frag = frag->next) {
		if (!frag->rejected)
			continue;
		cnt++;
	}

	if (!cnt) {
		if (apply_verbosely)
			say_patch_name(stderr,
				       _("Applied patch %s cleanly."), patch);
		return 0;
	}

	/* This should not happen, because a removal patch that leaves
	 * contents are marked "rejected" at the patch level.
	 */
	if (!patch->new_name)
		die(_("internal error"));

	/* Say this even without --verbose */
	strbuf_addf(&sb, Q_("Applying patch %%s with %d reject...",
			    "Applying patch %%s with %d rejects...",
			    cnt),
		    cnt);
	say_patch_name(stderr, sb.buf, patch);
	strbuf_release(&sb);

	cnt = strlen(patch->new_name);
	if (ARRAY_SIZE(namebuf) <= cnt + 5) {
		cnt = ARRAY_SIZE(namebuf) - 5;
		warning(_("truncating .rej filename to %.*s.rej"),
			cnt - 1, patch->new_name);
	}
	memcpy(namebuf, patch->new_name, cnt);
	memcpy(namebuf + cnt, ".rej", 5);

	rej = fopen(namebuf, "w");
	if (!rej)
		return error(_("cannot open %s: %s"), namebuf, strerror(errno));

	/* Normal git tools never deal with .rej, so do not pretend
	 * this is a git patch by saying --git or giving extended
	 * headers.  While at it, maybe please "kompare" that wants
	 * the trailing TAB and some garbage at the end of line ;-).
	 */
	fprintf(rej, "diff a/%s b/%s\t(rejected hunks)\n",
		patch->new_name, patch->new_name);
	for (cnt = 1, frag = patch->fragments;
	     frag;
	     cnt++, frag = frag->next) {
		if (!frag->rejected) {
			fprintf_ln(stderr, _("Hunk #%d applied cleanly."), cnt);
			continue;
		}
		fprintf_ln(stderr, _("Rejected hunk #%d."), cnt);
		fprintf(rej, "%.*s", frag->size, frag->patch);
		if (frag->patch[frag->size-1] != '\n')
			fputc('\n', rej);
	}
	fclose(rej);
	return -1;
}