(u[1] == '\n') {
					/* Trim escaped newline. */
					total_size -= 2;
					mtree->line.s[total_size] = '\0';
					break;
				} else if (u[1] != '\0') {
					/* Skip the two-char escape sequence */
					++u;
				}