                        repeat = 1;
                    }

                    issueCommandRepeat(argc-skipargs, argv+skipargs, repeat);

                    elapsed = mstime()-start_time;
                    if (elapsed >= 500) {
                        printf("(%.2fs)\n",(double)elapsed/1000);
