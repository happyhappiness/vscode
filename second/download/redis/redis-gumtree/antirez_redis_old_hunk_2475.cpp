                    (char*)c->argv[4]->ptr);
                return;
            }
            server.cluster.migrating_slots_to[slot] = n;
        } else if (!strcasecmp(c->argv[3]->ptr,"importing") && c->argc == 5) {
            if (server.cluster.slots[slot] == server.cluster.myself) {
                addReplyErrorFormat(c,
                    "I'm already the owner of hash slot %u",slot);
                return;
