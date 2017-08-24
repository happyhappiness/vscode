(!safe_char[*(const unsigned char *)pp]) {
			if (*pp != ' ' && *pp != '\t' && *pp != '\r'
			    && *pp != '\n')
				f = 0;
			break;
		}