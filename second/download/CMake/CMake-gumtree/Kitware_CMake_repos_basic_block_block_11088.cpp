{
		archive_wstrcpy(&(cab->ws), wp);
		for (i = 0; i < archive_strlen(&(cab->ws)); i++) {
			if (cab->ws.s[i] == L'\\')
				cab->ws.s[i] = L'/';
		}
		archive_entry_copy_pathname_w(entry, cab->ws.s);
	}