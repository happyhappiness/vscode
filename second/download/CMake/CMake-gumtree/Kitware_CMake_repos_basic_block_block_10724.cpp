(i = 0; i < ci->numFolders; i++) {
			if (read_Folder(a, &(ci->folders[i])) < 0)
				goto failed;
		}