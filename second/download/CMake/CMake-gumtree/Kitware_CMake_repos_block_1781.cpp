{
			if ((b % 2) == 0)
				printf("\n\t\t");

			printf("UINT64_C(0x%016" PRIX64 ")",
					crc64_table[s][b]);

			if (b != 255)
				printf(",%s", (b+1) % 2 == 0 ? "" : " ");
		}