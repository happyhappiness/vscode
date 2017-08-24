{
			*slash = L'\0';
			r = create_dir(a, path);
			*slash = L'\\';
			return (r);
		}