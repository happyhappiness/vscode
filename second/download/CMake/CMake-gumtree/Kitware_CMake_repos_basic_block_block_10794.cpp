((entries[i].mode & AE_IFMT) == AE_IFDIR &&
			    entries[i].name_len >= 2 &&
			    (entries[i].utf16name[entries[i].name_len-2] != '/' ||
			     entries[i].utf16name[entries[i].name_len-1] != 0)) {
				entries[i].utf16name[entries[i].name_len] = '/';
				entries[i].utf16name[entries[i].name_len+1] = 0;
				entries[i].name_len += 2;
			}