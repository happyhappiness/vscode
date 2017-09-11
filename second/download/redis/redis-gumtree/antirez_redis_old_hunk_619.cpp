            rewriteClientCommandArgument(c,0,
                resetRefCount(createStringObject("EVAL",4)));
            rewriteClientCommandArgument(c,1,script);
            printf("forceCommandPropagation\n");
            forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
        }
    }
