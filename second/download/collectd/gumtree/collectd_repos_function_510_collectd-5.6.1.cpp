static int nfs_submit_nfs4_server (const char *instance, char **fields,
		size_t fields_num)
{
	static int suppress_warning = 0;

	if (fields_num != NFS4_SERVER40_NUM_PROC &&
		fields_num != NFS4_SERVER41_NUM_PROC)
	{
		if (!suppress_warning)
		{
			WARNING ("nfs plugin: Unexpected number of fields for "
					"NFSv4 %s statistics: %zu. ",
					instance, fields_num);
		}

		if (fields_num > NFS4_SERVER_MAX_PROC)
		{
			fields_num = NFS4_SERVER_MAX_PROC;
			suppress_warning = 1;
		}
		else
		{
			return (EINVAL);
		}
	}

        nfs_submit_fields (4, instance, fields,
			nfs4_server40_procedures_names_num,
			nfs4_server40_procedures_names);

	if (fields_num >= NFS4_SERVER41_NUM_PROC)
	{
		fields += nfs4_server40_procedures_names_num;

	        nfs_submit_fields (4, instance, fields,
				nfs4_server41_procedures_names_num,
				nfs4_server41_procedures_names);
	}

	return (0);
}