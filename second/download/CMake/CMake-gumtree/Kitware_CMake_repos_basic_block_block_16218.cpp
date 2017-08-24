(p[0] == '/') {
			if (p[1] == '/')
				/* Convert '//' --> '/' */
				strcpy(p, p+1);
			else if (p[1] == '.' && p[2] == '/')
				/* Convert '/./' --> '/' */
				strcpy(p, p+2);
			else if (p[1] == '.' && p[2] == '.' && p[3] == '/') {
				/* Convert 'dir/dir1/../dir2/'
				 *     --> 'dir/dir2/'
				 */
				char *rp = p -1;
				while (rp >= dirname) {
					if (*rp == '/')
						break;
					--rp;
				}
				if (rp > dirname) {
					strcpy(rp, p+3);
					p = rp;
				} else {
					strcpy(dirname, p+4);
					p = dirname;
				}
			} else
				p++;
		} else
			p++