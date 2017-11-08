static void cleanup_thread(HANDLE *handles, int *thread_cnt,
                           int thread_to_clean)
{
    int i;

    CloseHandle(handles[thread_to_clean]);
    for (i = thread_to_clean; i < ((*thread_cnt) - 1); i++)
        handles[i] = handles[i + 1];
    (*thread_cnt)--;
}