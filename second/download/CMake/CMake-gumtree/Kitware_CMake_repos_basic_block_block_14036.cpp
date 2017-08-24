{
				/* Current byte sequence may be CESU-8. */
				n = cesu8_to_unicode(&uc, s, len);
			}