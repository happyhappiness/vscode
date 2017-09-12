            redisLog(REDIS_WARNING,"Aborting on short write while writing to the append-only file: %s",strerror(errno));
         }
         abort();
     }
     fsync(server.appendfd); /* Let's try to get this data on the disk */
}

static void processInputBuffer(redisClient *c) {
