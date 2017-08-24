{
			bname += 1;
			memmove(bname + 2, bname, strlen(bname) + 1);
			memmove(bname, "._", 2);
		}