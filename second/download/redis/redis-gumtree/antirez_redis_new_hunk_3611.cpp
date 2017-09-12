                            cliSendCommand(argc,argv,1);
                        }
                    }
                    elapsed = mstime()-start_time;
                    if (elapsed > 500) printf("%.2f seconds\n",
                        (double)elapsed/1000);
                }
            }
            /* Free the argument vector */
