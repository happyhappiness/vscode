{
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