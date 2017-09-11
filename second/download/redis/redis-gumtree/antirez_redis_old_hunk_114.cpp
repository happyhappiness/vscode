        exit(1);
    } else if (c->err) {
        printf("Connection error: %s\n", c->errstr);
        exit(1);
    }

