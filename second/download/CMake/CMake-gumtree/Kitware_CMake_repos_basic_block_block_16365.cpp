{
		char *dot, *xdot;
		int ext_off, noff, weight;

		l = (int)np->file->basename.length;
		p = malloc(l+31+2+1);
		if (p == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory");
			return (ARCHIVE_FATAL);
		}
		memcpy(p, np->file->basename.s, l);
		p[l] = '\0';
		np->identifier = p;

		dot = xdot = NULL;
		if (!allow_ldots) {
			/*
			 * If there is a '.' character at the first byte,
			 * it has to be replaced by '_' character.
			 */
			if (*p == '.')
				*p++ = '_';
		}
		for (;*p; p++) {
			if (*p & 0x80) {
				*p = '_';
				continue;
			}
			if (char_map[(unsigned char)*p]) {
				/* if iso-level is '4', a character '.' is
				 * allowed by char_map. */
				if (*p == '.') {
					xdot = dot;
					dot = p;
				}
				continue;
			}
			if (*p >= 'a' && *p <= 'z') {
				*p -= 'a' - 'A';
				continue;
			}
			if (*p == '.') {
				xdot = dot;
				dot = p;
				if (allow_multidot)
					continue;
			}
			*p = '_';
		}
		p = np->identifier;
		weight = -1;
		if (dot == NULL) {
			int nammax;

			if (np->dir)
				nammax = dnmax;
			else
				nammax = fnmax;

			if (l > nammax) {
				p[nammax] = '\0';
				weight = nammax;
				ext_off = nammax;
			} else
				ext_off = l;
		} else {
			*dot = '.';
			ext_off = (int)(dot - p);

			if (iso9660->opt.iso_level == 1) {
				if (dot - p <= 8) {
					if (strlen(dot) > 4) {
						/* A length of a file extension
						 * must be less than 4 */
						dot[4] = '\0';
						weight = 0;
					}
				} else {
					p[8] = dot[0];
					p[9] = dot[1];
					p[10] = dot[2];
					p[11] = dot[3];
					p[12] = '\0';
					weight = 8;
					ext_off = 8;
				}
			} else if (np->dir) {
				if (l > dnmax) {
					p[dnmax] = '\0';
					weight = dnmax;
					if (ext_off > dnmax)
						ext_off = dnmax;
				}
			} else if (l > ffmax) {
				int extlen = (int)strlen(dot);
				int xdoff;

				if (xdot != NULL)
					xdoff = (int)(xdot - p);
				else
					xdoff = 0;

				if (extlen > 1 && xdoff < fnmax-1) {
					int off;

					if (extlen > ffmax)
						extlen = ffmax;
					off = ffmax - extlen;
					if (off == 0) {
						/* A dot('.')  character
						 * doesn't place to the first
						 * byte of identifier. */
						off ++;
						extlen --;
					}
					memmove(p+off, dot, extlen);
					p[ffmax] = '\0';
					ext_off = off;
					weight = off;
#ifdef COMPAT_MKISOFS
				} else if (xdoff >= fnmax-1) {
					/* Simulate a bug(?) of mkisofs. */
					p[fnmax-1] = '\0';
					ext_off = fnmax-1;
					weight = fnmax-1;
#endif
				} else {
					p[fnmax] = '\0';
					ext_off = fnmax;
					weight = fnmax;
				}
			}
		}
		/* Save an offset of a file name extension to sort files. */
		np->ext_off = ext_off;
		np->ext_len = (int)strlen(&p[ext_off]);
		np->id_len = l = ext_off + np->ext_len;

		/* Make an offset of the number which is used to be set
		 * hexadecimal number to avoid duplicate identifier. */
		if (iso9660->opt.iso_level == 1) {
			if (ext_off >= 5)
				noff = 5;
			else
				noff = ext_off;
		} else {
			if (l == ffmax)
				noff = ext_off - 3;
			else if (l == ffmax-1)
				noff = ext_off - 2;
			else if (l == ffmax-2)
				noff = ext_off - 1;
			else
				noff = ext_off;
		}
		/* Register entry to the identifier resolver. */
		idr_register(idr, np, weight, noff);
	}