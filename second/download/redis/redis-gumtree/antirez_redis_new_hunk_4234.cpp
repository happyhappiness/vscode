            deleted++;
        }
    }
    addReplyLong(c,deleted);
}

static void existsCommand(redisClient *c) {
