fprintf(debug_log, "\tTotal in use:          %6d KB %d%%\n",
            t >> 10, Math::intPercent(t, mp.arena));