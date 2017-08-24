(u[0] == '#') {
				/* Ends with comment sequence #...\n */
				if (nl == NULL) {
					/* But we've not found the \n yet */
					break;
				}
			}