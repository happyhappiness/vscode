storeAppendPrintf(sentry, "\tTotal free:            %6.0f KB %.0f%%\n",
                      static_cast<double>(ms.bytes_free / 1024),
                      Math::doublePercent(static_cast<double>(ms.bytes_free), static_cast<double>(ms.bytes_total)));