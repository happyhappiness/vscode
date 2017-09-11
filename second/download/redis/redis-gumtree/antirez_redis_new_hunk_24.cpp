 * Latency and latency history modes
 *--------------------------------------------------------------------------- */

static void latencyModePrint(long long min, long long max, double avg, long long count) {
    if (config.output == OUTPUT_STANDARD) {
        printf("min: %lld, max: %lld, avg: %.2f (%lld samples)",
                min, max, avg, count);
        fflush(stdout);
    } else if (config.output == OUTPUT_CSV) {
        printf("%lld,%lld,%.2f,%lld\n", min, max, avg, count);
    } else if (config.output == OUTPUT_RAW) {
        printf("%lld %lld %.2f %lld\n", min, max, avg, count);
    }
}

#define LATENCY_SAMPLE_RATE 10 /* milliseconds. */
#define LATENCY_HISTORY_DEFAULT_INTERVAL 15000 /* milliseconds. */
static void latencyMode(void) {
