{
			bp[1] = 'S';
			bp[2] = 'P';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			bp[5] = 0xBE;  /* Check Byte	*/
			bp[6] = 0xEF;  /* Check Byte	*/
			bp[7] = 0;
			bp += length;
		}