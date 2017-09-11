        }
        payload -= nread;
    }
    if (!config.raw_output) printf("SYNC done. Logging commands from master.\n");

    /* Now we can use the hiredis to read the incoming protocol. */
    while (cliReadReply(config.raw_output) == REDIS_OK);
}

int main(int argc, char **argv) {
