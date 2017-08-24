(sc->nconverter > 1) {
		sc->utftmp.length = 0;
		r2 = sc->converter[0](&(sc->utftmp), s, length, sc);
		if (r2 != 0 && errno == ENOMEM)
			return (r2);
		if (r > r2)
			r = r2;
		s = sc->utftmp.s;
		length = sc->utftmp.length;
		++i;
	}