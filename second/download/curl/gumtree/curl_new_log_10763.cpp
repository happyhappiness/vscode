warnf(config->global, "Transient problem: %s "
                    "Will retry in %ld seconds. "
                    "%ld retries left.\n",
                    m[retry], retry_sleep/1000L, retry_numretries);