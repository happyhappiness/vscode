(*p == '=') {
			int value = 0;
			++p;
			--len;
			while (len > 0 && *p != ' ' && *p != '\t') {
				++p;
				--len;
				value = 1;
			}
			/* A keyword should have a its value unless
			 * "/unset" operation. */ 
			if (!unset && value == 0)
				return (-1);
		}