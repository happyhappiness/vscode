(sl_last == '\0' && sl[0] == '/') {
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