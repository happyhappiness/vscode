        } else if (n == myself) {
            addReplyError(c,"I tried hard but I can't forget myself...");
            return;
        } else if (myself->flags & REDIS_NODE_SLAVE && myself->slaveof == n) {
            addReplyError(c,"Can't forget my master!");
            return;
        }
