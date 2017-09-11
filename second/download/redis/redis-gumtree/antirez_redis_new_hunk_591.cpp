
                    issueCommandRepeat(argc-skipargs, argv+skipargs, repeat);

                    /* If our debugging session ended, show the EVAL final
                     * reply. */
                    if (config.eval_ldb_end) {
                        config.eval_ldb_end = 0;
                        cliReadReply(0);
                        printf("\n(Lua debugging session ended)\n\n");
                    }

                    elapsed = mstime()-start_time;
                    if (elapsed >= 500) {
                        printf("(%.2fs)\n",(double)elapsed/1000);
