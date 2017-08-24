(fe = flagentry; fe->name != NULL; fe++) {
			if (fe->name[cp - p] != '\0'
			    || p[0] != fe->name[0])
				continue;
			if (strncmp(p, fe->name, cp - p) == 0) {
				avail[n++] = fe;
				break;
			}
		}