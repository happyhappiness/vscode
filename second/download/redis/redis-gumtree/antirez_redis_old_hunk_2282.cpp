            "Clear FAIL state for node %.40s: is reachable again and nobody is serving its slots after some time.",
                node->name);
        node->flags &= ~REDIS_NODE_FAIL;
        changes++;
    }

    /* Update state and save config. */
    if (changes) {
        clusterUpdateState();
        clusterSaveConfigOrDie();
    }
}

