{
				length = 5 + sllen;
				if (bp != NULL) {
					/*
					 * Mark flg as CONTINUE component.
					 */
					*cf |= 0x01;
					/*
					 *               len  ver  flg
					 *    +----+----+----+----+----+-
					 *    | 'S'| 'L'| XX | 01 | 01 |
					 *    +----+----+----+----+----+-
					 *                           ^
					 *           continues in next "SL"
					 */
					bp[3] = length;
					bp[5] = 0x01;/* This Symbolic Link
						      * continues in next
						      * "SL" field */
					bp += length;
				}
				extra_tell_used_size(&ctl, length);
				if (extra_space(&ctl) < 11)
					bp = extra_next_record(&ctl, 11);
				if (bp != NULL) {
					/* Next 'SL' */
					bp[1] = 'S';
					bp[2] = 'L';
					bp[4] = 1;    /* version */
				}
			}