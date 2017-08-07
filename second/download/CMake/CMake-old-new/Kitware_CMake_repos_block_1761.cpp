{
		if ((b % 4) == 0)
			printf("\n\t");

		printf("0x%08" PRIX32, crc32_table[0][b]);

		if (b != 255)
			printf(",%s", (b+1) % 4 == 0 ? "" : " ");
	}