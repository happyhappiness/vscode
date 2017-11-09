int ap_proxy_lb_workers(void)
{
    /*
     * Since we can't resize the scoreboard when reconfiguring, we
     * have to impose a limit on the number of workers, we are
     * able to reconfigure to.
     */
    if (!lb_workers_limit)
        lb_workers_limit = proxy_lb_workers + PROXY_DYNAMIC_BALANCER_LIMIT;
    return lb_workers_limit;
}