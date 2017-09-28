                     server.cluster->currentEpoch =
                             strtoull(argv[j+1],NULL,10);
                 } else if (strcasecmp(argv[j],"lastVoteEpoch") == 0) {
                     server.cluster->lastVoteEpoch =
                             strtoull(argv[j+1],NULL,10);
                 } else {
-                    redisLog(REDIS_WARNING,
+                    serverLog(LL_WARNING,
                         "Skipping unknown cluster config variable '%s'",
                         argv[j]);
                 }
             }
             sdsfreesplitres(argv,argc);
             continue;
