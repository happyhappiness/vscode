{
		/* Filename is last item on line. */
		/* Adjust line_len to trim trailing whitespace */
		while (line_len > 0) {
			char last_character = line[line_len - 1];
			if (last_character == '\r'
			    || last_character == '\n'
			    || last_character == '\t'
			    || last_character == ' ') {
				line_len--;
			} else {
				break;
			}
		}
		/* Name starts after the last whitespace separator */
		name = line;
		for (i = 0; i < line_len; i++) {
			if (line[i] == '\r'
			    || line[i] == '\n'
			    || line[i] == '\t'
			    || line[i] == ' ') {
				name = line + i + 1;
			}
		}
		name_len = line + line_len - name;
		end = name;
	}