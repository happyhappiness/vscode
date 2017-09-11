            printf("Max latency so far: %lld microseconds.\n", max_latency);
        }

        if (force_cancel_loop || end > test_end) {
            printf("\n%lld total runs (avg %lld microseconds per run).\n",
                runs, run_time/runs);
            printf("Worst run took %.02fx times the average.\n",
