                }
                ln = next;
            }
            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",removed));
        }
    }
}
