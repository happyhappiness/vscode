            }
            checked_standby = checking_standby++;
        }
        cur_lbset++;
    } while (cur_lbset <= max_lbset && !mycandidate);

    return mycandidate;
}

/*
 * How to add additional lbmethods:
 *   1. Create func which determines "best" candidate worker
 *      (eg: find_best_bytraffic, above)
