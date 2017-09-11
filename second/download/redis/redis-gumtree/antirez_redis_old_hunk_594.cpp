            /* Disconnection from the server signals end of EVAL
             * debugging session. */
            if (config.eval_ldb) {
                config.eval_ldb = 0;
                config.output = OUTPUT_STANDARD;
                cliRefreshPrompt();
