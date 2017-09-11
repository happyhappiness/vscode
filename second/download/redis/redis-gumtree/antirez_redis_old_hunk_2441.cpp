        }

        /* Set the master. */
        clusterSetMaster(n);
        clusterUpdateState();
        clusterSaveConfigOrDie();
