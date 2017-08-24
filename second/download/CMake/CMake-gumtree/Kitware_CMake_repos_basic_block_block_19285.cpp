{
  uv_cpu_info_t* cpu_info;
  int result;
  int idx;
  siv1v2 info;
  data_area_ptr cvt = {0};
  data_area_ptr csd = {0};
  data_area_ptr rmctrct = {0};
  data_area_ptr cvtopctp = {0};
  int cpu_usage_avg;

  cvt.assign = *(data_area_ptr_assign_type*)(CVT_PTR);

  csd.assign = *((data_area_ptr_assign_type *) (cvt.deref + CSD_OFFSET));
  cvtopctp.assign = *((data_area_ptr_assign_type *) (cvt.deref + CVTOPCTP_OFFSET));
  rmctrct.assign = *((data_area_ptr_assign_type *) (cvtopctp.deref + RMCTRCT_OFFSET));

  *count = *((int*) (csd.deref + CSD_NUMBER_ONLINE_CPUS));
  cpu_usage_avg = *((unsigned short int*) (rmctrct.deref + RCTLACS_OFFSET));

  *cpu_infos = uv__malloc(*count * sizeof(uv_cpu_info_t));
  if (!*cpu_infos)
    return -ENOMEM;

  cpu_info = *cpu_infos;
  idx = 0;
  while (idx < *count) {
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

  return 0;
}