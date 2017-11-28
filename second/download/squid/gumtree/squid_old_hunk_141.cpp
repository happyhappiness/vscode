            perror("unlink");
        }

        return -errno;
    }

    DEBUG(2)
    fprintf(stderr, "%d UNLNK %s\n", (int) mypid, buf);
    return 0;
}

static void
msg_handle(diomsg * r, int rl, diomsg * s)
{
