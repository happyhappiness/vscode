storeAppendPrintf(&output, "Current Capacity       : %" PRId64 "%% used, %" PRId64 "%% free\n",
                      Math::int64Percent(store_swap_size, maxSize()),
                      Math::int64Percent((maxSize() - store_swap_size), maxSize()));