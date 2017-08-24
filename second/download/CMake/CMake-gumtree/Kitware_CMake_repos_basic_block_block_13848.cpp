(!(sc->flag &
			    (SCONV_NORMALIZATION_D |SCONV_NORMALIZATION_C)))
				add_converter(sc,
				    archive_string_append_unicode)