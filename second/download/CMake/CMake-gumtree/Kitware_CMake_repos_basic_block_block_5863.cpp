f(pipeLen >= httpc->settings.max_concurrent_streams) {
              infof(data, "MAX_CONCURRENT_STREAMS reached, skip (%zu)\n",
                    pipeLen);
              continue;
            }