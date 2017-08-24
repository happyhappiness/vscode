{
    cpu_info->speed = *(int*)(info.siv1v2si22v1.si22v1cpucapability);
    cpu_info->model = uv__malloc(CPCMODEL_LENGTH + 1);
    memset(cpu_info->model, '\0', CPCMODEL_LENGTH + 1);
    memcpy(cpu_info->model, info.siv1v2si11v1.si11v1cpcmodel, CPCMODEL_LENGTH);
    cpu_info->cpu_times.user = cpu_usage_avg;
    /* TODO: implement the following */
    cpu_info->cpu_times.sys = 0;
    cpu_info->cpu_times.idle = 0;
    cpu_info->cpu_times.irq = 0;
    cpu_info->cpu_times.nice = 0;
    ++cpu_info;
    ++idx;
  }