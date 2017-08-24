{
			*--t = "0123456789"[digit];
			digit = nanos % 10;
			nanos /= 10;
			i--;
		}