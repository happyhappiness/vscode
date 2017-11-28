storeAppendPrintf(sentry, "\tAverage HTTP requests per minute since start:\t%.1f\n",
                      statCounter.client_http.requests / (runtime / 60.0));