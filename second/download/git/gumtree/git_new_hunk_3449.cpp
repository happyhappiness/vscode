	if (rename(tmp, path) < 0)
		goto out;
	ret = 0;

out:
	if (ret) {
		error_errno("unable to update %s", path);
		if (fp)
			fclose(fp);
		else if (fd >= 0)
			close(fd);
		unlink(tmp);
	}
