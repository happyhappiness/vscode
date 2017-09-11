    exit(0);
}

/*------------------------------------------------------------------------------
 * Intrisic latency mode.
 *
 * Measure max latency of a running process that does not result from
 * syscalls. Basically this software should provide an hint about how much
 * time the kernel leaves the process without a chance to run.
 *--------------------------------------------------------------------------- */

/* This is just some computation the compiler can't optimize out.
 * Should run in less than 100-200 microseconds even using very
 * slow hardware. Runs in less than 10 microseconds in modern HW. */
uint64_t compute_something_fast(void) {
    uint8_t s[256], i, j, t;
    int count = 1000, k;
    uint64_t output = 0;

    for (k = 0; k < 256; k++) s[k] = k;

    i = 0;
    j = 0;
    while(count--) {
        i++;
        j = j + s[i];
        t = s[i];
        s[i] = s[j];
        s[j] = t;
        output += s[(s[i]+s[j])&255];
    }
    return output;
}

static void intrinsicLatencyMode(void) {
    long long test_end, run_time, max_latency = 0, runs = 0;

    run_time = config.intrinsic_latency_duration*1000000;
    test_end = ustime() + run_time;

    while(1) {
        long long start, end, latency;

        start = ustime();
        compute_something_fast();
        end = ustime();
        latency = end-start;
        runs++;
        if (latency <= 0) continue;

        /* Reporting */
        if (latency > max_latency) {
            max_latency = latency;
            printf("Max latency so far: %lld microseconds.\n", max_latency);
        }

        if (end > test_end) {
            printf("\n%lld total runs (avg %lld microseconds per run).\n",
                runs, run_time/runs);
            printf("Worst run took %.02fx times the avarege.\n",
                (double) max_latency / (run_time/runs));
            exit(0);
        }
    }
}

/*------------------------------------------------------------------------------
 * Program main()
 *--------------------------------------------------------------------------- */

int main(int argc, char **argv) {
    int firstarg;

