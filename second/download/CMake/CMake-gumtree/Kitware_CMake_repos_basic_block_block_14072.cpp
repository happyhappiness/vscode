((cl = CCC(uc2)) == 0) {
				/* Clearly 'uc2' the second code point is not
				 * a decomposable code. */
				WRITE_UC();
				REPLACE_UC_WITH_UC2();
				continue;
			}