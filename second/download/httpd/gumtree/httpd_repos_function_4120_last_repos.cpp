void ap_mpm_pod_killpg(ap_pod_t *pod, int num)
{
    int i;
    apr_status_t rv = APR_SUCCESS;

    /* we don't write anything to the pod here...  we assume
     * that the would-be reader of the pod has another way to
     * see that it is time to die once we wake it up
     *
     * writing lots of things to the pod at once is very
     * problematic... we can fill the kernel pipe buffer and
     * be blocked until somebody consumes some bytes or
     * we hit a timeout...  if we hit a timeout we can't just
     * keep trying because maybe we'll never successfully
     * write again...  but then maybe we'll leave would-be
     * readers stranded (a number of them could be tied up for
     * a while serving time-consuming requests)
     */
    /* Recall: we only worry about IDLE child processes here */
    for (i = 0; i < num && rv == APR_SUCCESS; i++) {
        if (ap_scoreboard_image->servers[i][0].status != SERVER_READY ||
            ap_scoreboard_image->servers[i][0].pid == 0) {
            continue;
        }
        rv = dummy_connection(pod);
    }
}