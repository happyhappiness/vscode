die("attempting to mmap %"PRIuMAX" over limit %"PRIuMAX,
		    (uintmax_t)length, (uintmax_t)limit);