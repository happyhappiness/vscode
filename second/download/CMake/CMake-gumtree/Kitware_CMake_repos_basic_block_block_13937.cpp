{
			sc->flag |= SCONV_NORMALIZATION_D;
			sc->flag &= ~SCONV_NORMALIZATION_C;
			/* Set up string converters. */
			setup_converter(sc);
		}