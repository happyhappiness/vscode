storeAppendPrintf(sentry, "\tSmall blocks:          %6.0f KB %6.0f blks\n",
                      static_cast<double>(mp.usmblks / 1024), static_cast<double>(mp.smblks));