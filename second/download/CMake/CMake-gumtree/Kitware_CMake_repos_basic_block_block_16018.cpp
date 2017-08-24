{
		/*
		 *   "SL" Format:
		 *     e.g. a symbolic name is 'foo/bar'
		 *               len  ver  flg
		 *    +----+----+----+----+----+------------+
		 *    | 'S'| 'L'| 0F | 01 | 00 | components |
		 *    +----+----+----+----+----+-----+------+
		 *    0    1    2    3    4    5  ...|...  15
		 *    <----------------- len --------+------>
		 *    components :                   |
		 *     cflg clen                     |
		 *    +----+----+----+----+----+     |
		 *    | 00 | 03 | 'f'| 'o'| 'o'| <---+
		 *    +----+----+----+----+----+     |
		 *    5    6    7    8    9   10     |
		 *     cflg clen                     |
		 *    +----+----+----+----+----+     |
		 *    | 00 | 03 | 'b'| 'a'| 'r'| <---+
		 *    +----+----+----+----+----+
		 *   10   11   12   13   14   15
		 *
		 *    - cflg : flag of component
		 *    - clen : length of component
		 */
		const char *sl;
		char sl_last;

		if (extra_space(&ctl) < 7)
			bp = extra_next_record(&ctl, 7);
		sl = file->symlink.s;
		sl_last = '\0';
		if (bp != NULL) {
			bp[1] = 'S';
			bp[2] = 'L';
			bp[4] = 1;	/* version	*/
		}
		for (;;) {
			unsigned char *nc, *cf,  *cl, cldmy = 0;
			int sllen, slmax;

			slmax = extra_space(&ctl);
			if (slmax > 0xff)
				slmax = 0xff;
			if (bp != NULL)
				nc = &bp[6];
			else
				nc = NULL;
			cf = cl = NULL;
			sllen = 0;
			while (*sl && sllen + 11 < slmax) {
				if (sl_last == '\0' && sl[0] == '/') {
					/*
					 *     flg  len
					 *    +----+----+
					 *    | 08 | 00 | ROOT component.
					 *    +----+----+ ("/")
					 *
				 	 * Root component has to appear
				 	 * at the first component only.
					 */
					if (nc != NULL) {
						cf = nc++;
						*cf = 0x08; /* ROOT */
						*nc++ = 0;
					}
					sllen += 2;
					sl++;
					sl_last = '/';
					cl = NULL;
					continue;
				}
				if (((sl_last == '\0' || sl_last == '/') &&
				      sl[0] == '.' && sl[1] == '.' &&
				     (sl[2] == '/' || sl[2] == '\0')) ||
				    (sl[0] == '/' &&
				      sl[1] == '.' && sl[2] == '.' &&
				     (sl[3] == '/' || sl[3] == '\0'))) {
					/*
					 *     flg  len
					 *    +----+----+
					 *    | 04 | 00 | PARENT component.
					 *    +----+----+ ("..")
					 */
					if (nc != NULL) {
						cf = nc++;
						*cf = 0x04; /* PARENT */
						*nc++ = 0;
					}
					sllen += 2;
					if (sl[0] == '/')
						sl += 3;/* skip "/.." */
					else
						sl += 2;/* skip ".." */
					sl_last = '.';
					cl = NULL;
					continue;
				}
				if (((sl_last == '\0' || sl_last == '/') &&
				      sl[0] == '.' &&
				     (sl[1] == '/' || sl[1] == '\0')) ||
				    (sl[0] == '/' && sl[1] == '.' &&
				     (sl[2] == '/' || sl[2] == '\0'))) {
					/*
					 *     flg  len
					 *    +----+----+
					 *    | 02 | 00 | CURRENT component.
					 *    +----+----+ (".")
					 */
					if (nc != NULL) {
						cf = nc++;
						*cf = 0x02; /* CURRENT */
						*nc++ = 0;
					}
					sllen += 2;
					if (sl[0] == '/')
						sl += 2;/* skip "/." */
					else
						sl ++;  /* skip "." */
					sl_last = '.';
					cl = NULL;
					continue;
				}
				if (sl[0] == '/' || cl == NULL) {
					if (nc != NULL) {
						cf = nc++;
						*cf = 0;
						cl = nc++;
						*cl = 0;
					} else
						cl = &cldmy;
					sllen += 2;
					if (sl[0] == '/') {
						sl_last = *sl++;
						continue;
					}
				}
				sl_last = *sl++;
				if (nc != NULL) {
					*nc++ = sl_last;
					(*cl) ++;
				}
				sllen++;
			}
			if (*sl) {
				length = 5 + sllen;
				if (bp != NULL) {
					/*
					 * Mark flg as CONTINUE component.
					 */
					*cf |= 0x01;
					/*
					 *               len  ver  flg
					 *    +----+----+----+----+----+-
					 *    | 'S'| 'L'| XX | 01 | 01 |
					 *    +----+----+----+----+----+-
					 *                           ^
					 *           continues in next "SL"
					 */
					bp[3] = length;
					bp[5] = 0x01;/* This Symbolic Link
						      * continues in next
						      * "SL" field */
					bp += length;
				}
				extra_tell_used_size(&ctl, length);
				if (extra_space(&ctl) < 11)
					bp = extra_next_record(&ctl, 11);
				if (bp != NULL) {
					/* Next 'SL' */
					bp[1] = 'S';
					bp[2] = 'L';
					bp[4] = 1;    /* version */
				}
			} else {
				length = 5 + sllen;
				if (bp != NULL) {
					bp[3] = length;
					bp[5] = 0;
					bp += length;
				}
				extra_tell_used_size(&ctl, length);
				break;
			}
		}
	}