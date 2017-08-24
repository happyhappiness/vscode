{
				/*
				 * SP extension stores the suspOffset
				 * (Number of bytes to skip between
				 * filename and SUSP records.)
				 * It is mandatory by the SUSP standard
				 * (IEEE 1281).
				 *
				 * It allows SUSP to coexist with
				 * non-SUSP uses of the System
				 * Use Area by placing non-SUSP data
				 * before SUSP data.
				 *
				 * SP extension must be in the root
				 * directory entry, disable all SUSP
				 * processing if not found.
				 */
				iso9660->suspOffset = p[6];
				iso9660->seenSUSP = 1;
				rr_start += 7;
			}