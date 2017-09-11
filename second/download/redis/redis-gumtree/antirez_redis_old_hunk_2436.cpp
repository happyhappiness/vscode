
        usleep(utime);
        addReply(c,shared.ok);
    } else {
        addReplyError(c,
            "Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|SWAPIN <key>|SWAPOUT <key>|RELOAD]");
    }
}

