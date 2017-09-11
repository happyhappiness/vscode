        }

        double avg_us = (double)run_time/runs;
        double avg_ns = avg_us * 10e3;
        if (force_cancel_loop || end > test_end) {
            printf("\n%lld total runs "
                "(avg latency: "
