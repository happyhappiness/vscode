{
			*slash = '\0';
			r = create_dir(a, path);
			*slash = '/';
			return (r);
		}