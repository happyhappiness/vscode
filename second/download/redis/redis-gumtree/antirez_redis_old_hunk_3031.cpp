}

void zcountCommand(redisClient *c) {
    genericZrangebyscoreCommand(c,0,1);
}

void zcardCommand(redisClient *c) {
