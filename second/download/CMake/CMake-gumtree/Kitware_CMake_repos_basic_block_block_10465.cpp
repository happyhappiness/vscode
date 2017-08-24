(len - nl >= 11 && memcmp(b, "begin ", 6) == 0)
				l = 6;
			else if (len - nl >= 18 &&
			    memcmp(b, "begin-base64 ", 13) == 0)
				l = 13;
			else
				l = 0