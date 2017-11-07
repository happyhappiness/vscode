printf("%s%.*s%s%s", color, (int)(eol - bol), bol, reset,
		       *eol ? "\n" : "");