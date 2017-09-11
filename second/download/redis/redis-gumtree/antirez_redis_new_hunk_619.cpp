            rewriteClientCommandArgument(c,0,
                resetRefCount(createStringObject("EVAL",4)));
            rewriteClientCommandArgument(c,1,script);
            forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
        }
    }
