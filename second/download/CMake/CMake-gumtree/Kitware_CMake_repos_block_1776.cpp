{
		if (i % 8 == 0)
			printf("\n\t");

		printf("%4" PRIu32, rc_prices[i]);

		if (i != array_size - 1)
			printf(",");
	}