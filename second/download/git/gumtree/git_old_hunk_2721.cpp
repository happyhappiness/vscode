			ret = error("Could not write to %s", filename);
		else if (fclose(f))
			ret = error("Could not close %s", filename);
		free(result.ptr);
	}

	return ret;
}
