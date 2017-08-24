(sc = a->sconv; sc != NULL; sc = sc->next) {
		if (strcmp(sc->from_charset, fc) == 0 &&
		    strcmp(sc->to_charset, tc) == 0)
			break;
	}