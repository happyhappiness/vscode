(bytes < 0) {
					free(b[0]); free(b[1]); free(b[2]);
					return ((int)bytes);
				}