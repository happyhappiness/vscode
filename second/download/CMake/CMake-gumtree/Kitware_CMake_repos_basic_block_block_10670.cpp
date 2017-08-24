(i = 0; i< f->numCoders; i++) {
			free(f->coders[i].properties);
		}