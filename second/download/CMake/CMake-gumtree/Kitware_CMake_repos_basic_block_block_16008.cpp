(sl[0] == '/' || cl == NULL) {
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