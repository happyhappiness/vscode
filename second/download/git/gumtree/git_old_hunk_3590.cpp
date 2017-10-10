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

#define swap(a,b) myswap((a),(b),sizeof(a))
