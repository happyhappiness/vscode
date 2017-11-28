int
Store::Controller::callback()
{
    /* This will likely double count. Thats ok. */
    PROF_start(storeDirCallback);

    /* mem cache callbacks ? */
    int result = swapDir->callback();

    PROF_stop(storeDirCallback);

    return result;
}