                    clientDone(c);
                    return;
                }
                /* Leave all the rest in the input buffer */
                c->ibuf = sdsrange(c->ibuf,(p-c->ibuf)+1,-1);
                goto processdata;
