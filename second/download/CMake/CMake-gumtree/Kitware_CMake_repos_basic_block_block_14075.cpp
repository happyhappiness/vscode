(0 <= VIndex && VIndex < HC_VCOUNT) {
					/* Make syllable of form LV. */
					UPDATE_UC(HC_SBASE +
					    (LIndex * HC_VCOUNT + VIndex) *
					     HC_TCOUNT);
				} else {
					WRITE_UC();
					REPLACE_UC_WITH_UC2();
				}