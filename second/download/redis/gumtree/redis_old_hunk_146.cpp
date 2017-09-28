                if(!maxkeys[type]) {
                    fprintf(stderr, "Failed to allocate memory for key!\n");
                    exit(1);
                }

                /* Keep track of the biggest size for this type */
                biggest[type] = sizes[i];                
            }

            /* Update overall progress */
            if(sampled % 1000000 == 0) {
                printf("[%05.2f%%] Sampled %llu keys so far\n", pct, sampled);
            }
        }

        /* Sleep if we've been directed to do so */
        if(sampled && (sampled %100) == 0 && config.interval) {
            usleep(config.interval);
        }
        
        freeReplyObject(reply);
    } while(it != 0);

    if(types) zfree(types);
    if(sizes) zfree(sizes);

