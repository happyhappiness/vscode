static int mic_read_cpu(int mic)
{
	MicCoreUtil core_util;
	MicCoreJiff core_jiffs[MAX_CORES];
	U32 core_jiffs_size;
	U32 status;

	core_jiffs_size = MAX_CORES * sizeof(MicCoreJiff);
	status = MicGetCoreUtilization(mic_handle, &core_util,
			core_jiffs, &core_jiffs_size);
	if (status != MIC_ACCESS_API_SUCCESS) {
		ERROR("mic plugin: Problem getting CPU utilization: %s",
				MicGetErrorString(status));
		return(-1);
	}

	if (show_cpu) {
		mic_submit_cpu(mic, "user", -1, core_util.sum.user);
		mic_submit_cpu(mic, "sys", -1, core_util.sum.sys);
		mic_submit_cpu(mic, "nice", -1, core_util.sum.nice);
		mic_submit_cpu(mic, "idle", -1, core_util.sum.idle);
	}

	if (show_cpu_cores) {
		int j;
		for (j = 0; j < core_util.core; j++) {
			mic_submit_cpu(mic, "user", j, core_jiffs[j].user);
			mic_submit_cpu(mic, "sys", j, core_jiffs[j].sys);
			mic_submit_cpu(mic, "nice", j, core_jiffs[j].nice);
			mic_submit_cpu(mic, "idle", j, core_jiffs[j].idle);
		}
	}
	return (0);
}