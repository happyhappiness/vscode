	}

	if ((batch.follow_symlinks || batch.all_objects) && !batch.enabled) {
		usage_with_options(cat_file_usage, options);
	}

	if (batch.buffer_output < 0)
		batch.buffer_output = batch.all_objects;

	if (batch.enabled)
		return batch_objects(&batch);

	if (unknown_type && opt != 't' && opt != 's')
		die("git cat-file --allow-unknown-type: use with -s or -t");
	return cat_one_file(opt, exp_type, obj_name, unknown_type);
