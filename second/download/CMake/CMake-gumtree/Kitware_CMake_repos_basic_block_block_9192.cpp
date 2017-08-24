{
		(void)gettimeofday(&rdat.tv, NULL);
		rdat.pid = getpid();
		/* We'll just take whatever was on the stack too... */
	}