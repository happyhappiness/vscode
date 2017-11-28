storeAppendPrintf(sentry, "\tTotal accounted:       %6.0f KB %.0f%%\n",
                      (statMemoryAccounted() / 1024), Math::doublePercent(statMemoryAccounted(), t));