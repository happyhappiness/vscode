        }
        payload -= nread;
    }
    fprintf(stderr,"SYNC done. Logging commands from master.\n");

    /* Now we can use the hiredis to read the incoming protocol. */
    config.output = OUTPUT_CSV;
    while (cliReadReply(0) == REDIS_OK);
}

int main(int argc, char **argv) {
