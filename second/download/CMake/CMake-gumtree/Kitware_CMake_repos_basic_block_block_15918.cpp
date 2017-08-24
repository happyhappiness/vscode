(wb_remaining(a) > 0) {
			ret = wb_write_out(a);
			if (ret < 0)
				return (ret);
		}