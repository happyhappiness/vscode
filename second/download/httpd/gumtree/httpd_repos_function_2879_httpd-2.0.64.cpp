static void proc_mutex_sysv_setup(void)
{
    proc_mutex_op_on.sem_num = 0;
    proc_mutex_op_on.sem_op = -1;
    proc_mutex_op_on.sem_flg = SEM_UNDO;
    proc_mutex_op_off.sem_num = 0;
    proc_mutex_op_off.sem_op = 1;
    proc_mutex_op_off.sem_flg = SEM_UNDO;
}