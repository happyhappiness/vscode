        decoded = sdstrim(decoded," ");
        addReplyBulkCBuffer(c,decoded,sdslen(decoded));
        sdsfree(decoded);
    } else {
        addReplyErrorFormat(c,"Unknown PFDEBUG subcommand '%s'", cmd);
    }
