{
			int nammax;

			if (np->dir)
				nammax = dnmax;
			else
				nammax = fnmax;

			if (l > nammax) {
				p[nammax] = '\0';
				weight = nammax;
				ext_off = nammax;
			} else
				ext_off = l;
		}