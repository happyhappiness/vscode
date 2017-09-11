        if (end > test_end) {
            printf("\n%lld total runs (avg %lld microseconds per run).\n",
                runs, run_time/runs);
            printf("Worst run took %.02fx times the avarege.\n",
                (double) max_latency / (run_time/runs));
            exit(0);
        }
