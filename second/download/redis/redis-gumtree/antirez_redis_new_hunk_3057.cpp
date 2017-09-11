
        /* Process the job accordingly to its type. */
        if (job->type == REDIS_BIO_CLOSE_FILE) {
            close((long)job->data);
        } else {
            redisPanic("Wrong job type in bioProcessBackgroundJobs().");
