			ret = error("Could not write to %s", filename);
		else if (fclose(f))
			ret = error("Could not close %s", filename);
		free(result.ptr);
	}

	if (ret > 127)
		ret = 127;

	return ret;
}
