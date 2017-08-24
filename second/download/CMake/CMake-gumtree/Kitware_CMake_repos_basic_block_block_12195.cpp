(p[0] == '#' || p[0] == '\n' || p[0] == '\r') {
				p += len;
				avail -= len;
				continue;
			}