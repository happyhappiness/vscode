fprintf(debug_log, "\tTotal free:            %6d KB %d%%\n",
            t >> 10, Math::intPercent(t, mp.arena));