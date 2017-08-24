{
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