    slowlogInit();
    bioInit();
    srand(time(NULL)^getpid());
}

/* Populates the Redis Command Table starting from the hard coded list
