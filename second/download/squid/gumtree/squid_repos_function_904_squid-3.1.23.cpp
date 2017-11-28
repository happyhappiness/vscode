void
comm_exit(void)
{
    delete TheHalfClosed;
    TheHalfClosed = NULL;

    safe_free(fd_table);
    safe_free(fdd_table);
    if (fdc_table) {
        delete[] fdc_table;
        fdc_table = NULL;
    }
    safe_free(commfd_table);
}