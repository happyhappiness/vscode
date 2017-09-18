printf("Time taken for tests:   %ld.%03ld seconds\n",
           (long) (timetakenusec / APR_USEC_PER_SEC),
           (long) (timetakenusec % APR_USEC_PER_SEC));