(u[0] == '\n') {
				/* Ends with unescaped newline. */
				*start = mtree->line.s;
				return total_size;
			} else if (u[0] == '#') {
				/* Ends with comment sequence #...\n */
				if (nl == NULL) {
					/* But we've not found the \n yet */
					break;
				}
			} else if (u[0] == '\\') {
				if (u[1] == '\n') {
					/* Trim escaped newline. */
					total_size -= 2;
					mtree->line.s[total_size] = '\0';
					break;
				} else if (u[1] != '\0') {
					/* Skip the two-char escape sequence */
					++u;
				}
			}