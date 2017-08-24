(p[H_METHOD_OFFSET+2] == 'h') {
			/* "-lh?-" */
			if (p[H_METHOD_OFFSET+3] == 's')
				break;
			if (p[H_LEVEL_OFFSET] == 0)
				return (0);
			if (p[H_LEVEL_OFFSET] <= 3 && p[H_ATTR_OFFSET] == 0x20)
				return (0);
		}