    storeAppendPrintf(sentry, "\tCPU Usage, 5 minute avg:\t%.2f%%\n",
                      stats.cpu_usage5);

    storeAppendPrintf(sentry, "\tCPU Usage, 60 minute avg:\t%.2f%%\n",
                      stats.cpu_usage60);

    storeAppendPrintf(sentry, "\tMaximum Resident Size: %.0f KB\n",
                      stats.maxrss);

    storeAppendPrintf(sentry, "\tPage faults with physical i/o: %.0f\n",
                      stats.page_faults);

