static int apply_filter(const char *path, const char *src, size_t len,
			int fd, struct strbuf *dst, struct convert_driver *drv,
			const unsigned int wanted_capability)
{
	const char *cmd = NULL;

	if (!drv)
		return 0;

	if (!dst)
		return 1;

	if ((CAP_CLEAN & wanted_capability) && !drv->process && drv->clean)
		cmd = drv->clean;
	else if ((CAP_SMUDGE & wanted_capability) && !drv->process && drv->smudge)
		cmd = drv->smudge;

	if (cmd && *cmd)
		return apply_single_file_filter(path, src, len, fd, dst, cmd);
	else if (drv->process && *drv->process)
		return apply_multi_file_filter(path, src, len, fd, dst, drv->process, wanted_capability);

	return 0;
}