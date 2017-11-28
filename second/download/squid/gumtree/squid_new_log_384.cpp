storeAppendPrintf(sentry, "\tTotal free:            %6.0f KB %.0f%%\n",
                      t / 1024, Math::doublePercent(t, stats.mp_arena + stats.mp_hblkhd));