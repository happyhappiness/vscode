{
		lastrm->prop_size = 0;
		free(lastrm->props);
		lastrm->props = NULL;
		return (lastrm->end(a, lastrm));
	}