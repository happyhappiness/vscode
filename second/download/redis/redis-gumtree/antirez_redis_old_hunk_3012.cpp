            else
                addReply(c,shared.czero);
        }
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
    }
