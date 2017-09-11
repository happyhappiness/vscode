            server.cluster->importing_slots_from[j] = server.cluster->slots[j];
        }
    }
    if (update_config) clusterSaveConfigOrDie(1);
    return REDIS_OK;
}

