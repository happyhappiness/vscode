{
			/* "Roll back" to client buffer. */
			filter->client_avail += filter->avail;
			filter->client_next -= filter->avail;
			/* Copy buffer is now empty. */
			filter->avail = 0;
			filter->next = filter->buffer;
			/* Return data from client buffer. */
			if (avail != NULL)
				*avail = filter->client_avail;
			return (filter->client_next);
		}