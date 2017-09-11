
        /* 4) Update state and save config. */
        clusterUpdateState();
        clusterSaveConfigOrDie();

        /* 5) Pong all the other nodes so that they can update the state
         *    accordingly and detect that we switched to master role. */
