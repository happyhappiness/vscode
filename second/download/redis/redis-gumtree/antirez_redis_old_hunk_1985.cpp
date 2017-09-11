        clusterSaveConfigOrDie(fsync);
    }

    /* Reset our flags. */
    server.cluster->todo_before_sleep = 0;
}

