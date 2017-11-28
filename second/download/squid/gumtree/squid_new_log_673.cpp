storeAppendPrintf(&output, "Current Capacity       : %.2f%% used, %.2f%% free\n",
                      Math::doublePercent(currentSize(), maxSize()),
                      Math::doublePercent((maxSize() - currentSize()), maxSize()));