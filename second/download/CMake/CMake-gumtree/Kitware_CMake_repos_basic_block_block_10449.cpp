(l >= 3 && b[0] == '=' && b[1] == '=' &&
			    b[2] == '=') {
				uudecode->state = ST_FIND_HEAD;
				break;
			}