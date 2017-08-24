{
/*
		void *data = (void *)__archive_read_ahead(a, *unconsumed, NULL);
		 * this block of code is to poison claimed unconsumed space, ensuring
		 * things break if it is in use still.
		 * currently it WILL break things, so enable it only for debugging this issue
		if (data) {
			memset(data, 0xff, *unconsumed);
		}
*/
		__archive_read_consume(a, *unconsumed);
		*unconsumed = 0;
	}