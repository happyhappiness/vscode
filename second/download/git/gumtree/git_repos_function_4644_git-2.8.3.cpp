static int parse_chunk(char *buffer, unsigned long size, struct patch *patch)
{
	int hdrsize, patchsize;
	int offset = find_header(buffer, size, &hdrsize, patch);

	if (offset < 0)
		return offset;

	prefix_patch(patch);

	if (!use_patch(patch))
		patch->ws_rule = 0;
	else
		patch->ws_rule = whitespace_rule(patch->new_name
						 ? patch->new_name
						 : patch->old_name);

	patchsize = parse_single_patch(buffer + offset + hdrsize,
				       size - offset - hdrsize, patch);

	if (!patchsize) {
		static const char git_binary[] = "GIT binary patch\n";
		int hd = hdrsize + offset;
		unsigned long llen = linelen(buffer + hd, size - hd);

		if (llen == sizeof(git_binary) - 1 &&
		    !memcmp(git_binary, buffer + hd, llen)) {
			int used;
			linenr++;
			used = parse_binary(buffer + hd + llen,
					    size - hd - llen, patch);
			if (used < 0)
				return -1;
			if (used)
				patchsize = used + llen;
			else
				patchsize = 0;
		}
		else if (!memcmp(" differ\n", buffer + hd + llen - 8, 8)) {
			static const char *binhdr[] = {
				"Binary files ",
				"Files ",
				NULL,
			};
			int i;
			for (i = 0; binhdr[i]; i++) {
				int len = strlen(binhdr[i]);
				if (len < size - hd &&
				    !memcmp(binhdr[i], buffer + hd, len)) {
					linenr++;
					patch->is_binary = 1;
					patchsize = llen;
					break;
				}
			}
		}

		/* Empty patch cannot be applied if it is a text patch
		 * without metadata change.  A binary patch appears
		 * empty to us here.
		 */
		if ((apply || check) &&
		    (!patch->is_binary && !metadata_changes(patch)))
			die(_("patch with only garbage at line %d"), linenr);
	}

	return offset + hdrsize + patchsize;
}