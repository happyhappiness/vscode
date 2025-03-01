static void pending_number(struct tm *tm, int *num)
{
	int number = *num;

	if (number) {
		*num = 0;
		if (tm->tm_mday < 0 && number < 32)
			tm->tm_mday = number;
		else if (tm->tm_mon < 0 && number < 13)
			tm->tm_mon = number-1;
		else if (tm->tm_year < 0) {
			if (number > 1969 && number < 2100)
				tm->tm_year = number - 1900;
			else if (number > 69 && number < 100)
				tm->tm_year = number;
			else if (number < 38)
				tm->tm_year = 100 + number;
			/* We screw up for number = 00 ? */
		}
	}
}