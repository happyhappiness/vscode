			usage_with_options(cat_file_usage, options);
	}
	if (batch.enabled && (opt || argc)) {
		usage_with_options(cat_file_usage, options);
	}

	if (batch.enabled)
		return batch_objects(&batch);

	return cat_one_file(opt, exp_type, obj_name);
}
