void
Store::Maintain(void *)
{
    Store::Root().maintain();

    /* Reregister a maintain event .. */
    eventAdd("MaintainSwapSpace", Maintain, NULL, 1.0, 1);

}