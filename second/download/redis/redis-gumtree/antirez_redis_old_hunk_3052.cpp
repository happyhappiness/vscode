        } else {
            if (latency < min) min = latency;
            if (latency > max) max = latency;
            avg = (double) tot/count;
        }
        printf("\x1b[0G\x1b[2Kmin: %lld, max: %lld, avg: %.2f (%lld samples)",
