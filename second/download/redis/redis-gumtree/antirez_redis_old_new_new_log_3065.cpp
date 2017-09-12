info = sdscatprintf(info,
        "# Profiling\r\n"
        "used_cpu_sys:%.2f\r\n"
        "used_cpu_user:%.2f\r\n"
        "used_cpu_sys_childrens:%.2f\r\n"
        "used_cpu_user_childrens:%.2f\r\n",
        (float)self_ru.ru_utime.tv_sec+(float)self_ru.ru_utime.tv_usec/1000000,
        (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
        (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000,
        (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000);