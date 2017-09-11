                return;
            }
        }
        sdsfree(sha);
        addReply(c,shared.ok);
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
    }
