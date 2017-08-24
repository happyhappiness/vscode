{
			sc->flag |= SCONV_NORMALIZATION_C;
			sc->flag &= ~SCONV_NORMALIZATION_D;
			/* Set up string converters. */
			setup_converter(sc);
		}