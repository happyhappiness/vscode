storeAppendPrintf(sentry, "\tmemPool accounted:     %6.0f KB %.0f%%\n",
                          static_cast<double>(mp_stats.TheMeter->alloc.level / 1024),
                          Math::doublePercent(static_cast<double>(mp_stats.TheMeter->alloc.level), t));