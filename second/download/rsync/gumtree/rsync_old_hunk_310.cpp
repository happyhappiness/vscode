		mkdir(fname,0777 & ~orig_umask); 
		*p = '/';
		p++;
	}
	return 0;
}
