                RAND_seed(stackdata+n, 128);
                nDone += 128;

            }
        }
    }
    ssl_log(s, SSL_LOG_INFO, "%sSeeding PRNG with %d bytes of entropy", prefix, nDone);

    if (RAND_status() == 0)
        ssl_log(s, SSL_LOG_WARN, "%sPRNG still contains not sufficient entropy!", prefix);

    return nDone;
}

#define BUFSIZE 8192

