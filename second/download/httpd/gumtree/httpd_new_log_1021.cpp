printf("Time per request:       %.3f [ms] (mean)\n", 
               (float) (1000 * concurrency * timetaken / done));