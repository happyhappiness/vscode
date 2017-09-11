        exit(1);
    } else if (c->err) {
        printf("Connection error: %s\n", c->errstr);
        redisFree(c);
        exit(1);
    }

