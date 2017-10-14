printf("Time per request:       %.3f [ms] (mean)\n",
               (double) concurrency * timetaken * 1000 / done);