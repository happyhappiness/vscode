                return;
            }
        }
        addReplyBulkCBuffer(c,funcname+2,40);
        sdsfree(sha);
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
    }
