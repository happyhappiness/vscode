        printf("\n");
        freeReplyObject(reply);
        usleep(config.interval);
    }
}

int main(int argc, char **argv) {
    int firstarg;

    config.hostip = sdsnew("127.0.0.1");
    config.hostport = 6379;
    config.hostsocket = NULL;
