            /* Disconnection from the server signals end of EVAL
             * debugging session. */
            if (config.eval_ldb) {
                printf("\n(Lua debugging session terminated)\n\n");
                config.eval_ldb = 0;
                config.output = OUTPUT_STANDARD;
                cliRefreshPrompt();
