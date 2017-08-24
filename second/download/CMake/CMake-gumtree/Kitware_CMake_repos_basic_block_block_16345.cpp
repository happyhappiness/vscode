(xdoff >= fnmax-1) {
					/* Simulate a bug(?) of mkisofs. */
					p[fnmax-1] = '\0';
					ext_off = fnmax-1;
					weight = fnmax-1;
#endif
				}