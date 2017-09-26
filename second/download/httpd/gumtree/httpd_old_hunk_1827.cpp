        }
        cur_lbset++;
    } while (cur_lbset <= max_lbset && !mycandidate);

    if (mycandidate) {
        mycandidate->s->lbstatus -= total_factor;
    }

    return mycandidate;
}

/*
