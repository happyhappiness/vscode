(i = 0; i < archive_strlen(&(lha->ws)); i++) {
			if (lha->ws.s[i] == L'\\')
				lha->ws.s[i] = L'/';
		}