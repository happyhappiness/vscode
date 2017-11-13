static void create_pack_file(void)
{
	struct child_process pack_objects = CHILD_PROCESS_INIT;
	char data[8193], progress[128];
	char abort_msg[] = "aborting due to possible repository "
		"corruption on the remote side.";
	int buffered = -1;
	ssize_t sz;
	int i;
	FILE *pipe_fd;

	if (shallow_nr) {
		argv_array_push(&pack_objects.args, "--shallow-file");
		argv_array_push(&pack_objects.args, "");
	}
	argv_array_push(&pack_objects.args, "pack-objects");
	argv_array_push(&pack_objects.args, "--revs");
	if (use_thin_pack)
		argv_array_push(&pack_objects.args, "--thin");

	argv_array_push(&pack_objects.args, "--stdout");
	if (shallow_nr)
		argv_array_push(&pack_objects.args, "--shallow");
	if (!no_progress)
		argv_array_push(&pack_objects.args, "--progress");
	if (use_ofs_delta)
		argv_array_push(&pack_objects.args, "--delta-base-offset");
	if (use_include_tag)
		argv_array_push(&pack_objects.args, "--include-tag");

	pack_objects.in = -1;
	pack_objects.out = -1;
	pack_objects.err = -1;
	pack_objects.git_cmd = 1;

	if (start_command(&pack_objects))
		die("git upload-pack: unable to fork git-pack-objects");

	pipe_fd = xfdopen(pack_objects.in, "w");

	if (shallow_nr)
		for_each_commit_graft(write_one_shallow, pipe_fd);

	for (i = 0; i < want_obj.nr; i++)
		fprintf(pipe_fd, "%s\n",
			oid_to_hex(&want_obj.objects[i].item->oid));
	fprintf(pipe_fd, "--not\n");
	for (i = 0; i < have_obj.nr; i++)
		fprintf(pipe_fd, "%s\n",
			oid_to_hex(&have_obj.objects[i].item->oid));
	for (i = 0; i < extra_edge_obj.nr; i++)
		fprintf(pipe_fd, "%s\n",
			oid_to_hex(&extra_edge_obj.objects[i].item->oid));
	fprintf(pipe_fd, "\n");
	fflush(pipe_fd);
	fclose(pipe_fd);

	/* We read from pack_objects.err to capture stderr output for
	 * progress bar, and pack_objects.out to capture the pack data.
	 */

	while (1) {
		struct pollfd pfd[2];
		int pe, pu, pollsize;
		int ret;

		reset_timeout();

		pollsize = 0;
		pe = pu = -1;

		if (0 <= pack_objects.out) {
			pfd[pollsize].fd = pack_objects.out;
			pfd[pollsize].events = POLLIN;
			pu = pollsize;
			pollsize++;
		}
		if (0 <= pack_objects.err) {
			pfd[pollsize].fd = pack_objects.err;
			pfd[pollsize].events = POLLIN;
			pe = pollsize;
			pollsize++;
		}

		if (!pollsize)
			break;

		ret = poll(pfd, pollsize,
			keepalive < 0 ? -1 : 1000 * keepalive);

		if (ret < 0) {
			if (errno != EINTR) {
				error_errno("poll failed, resuming");
				sleep(1);
			}
			continue;
		}
		if (0 <= pe && (pfd[pe].revents & (POLLIN|POLLHUP))) {
			/* Status ready; we ship that in the side-band
			 * or dump to the standard error.
			 */
			sz = xread(pack_objects.err, progress,
				  sizeof(progress));
			if (0 < sz)
				send_client_data(2, progress, sz);
			else if (sz == 0) {
				close(pack_objects.err);
				pack_objects.err = -1;
			}
			else
				goto fail;
			/* give priority to status messages */
			continue;
		}
		if (0 <= pu && (pfd[pu].revents & (POLLIN|POLLHUP))) {
			/* Data ready; we keep the last byte to ourselves
			 * in case we detect broken rev-list, so that we
			 * can leave the stream corrupted.  This is
			 * unfortunate -- unpack-objects would happily
			 * accept a valid packdata with trailing garbage,
			 * so appending garbage after we pass all the
			 * pack data is not good enough to signal
			 * breakage to downstream.
			 */
			char *cp = data;
			ssize_t outsz = 0;
			if (0 <= buffered) {
				*cp++ = buffered;
				outsz++;
			}
			sz = xread(pack_objects.out, cp,
				  sizeof(data) - outsz);
			if (0 < sz)
				;
			else if (sz == 0) {
				close(pack_objects.out);
				pack_objects.out = -1;
			}
			else
				goto fail;
			sz += outsz;
			if (1 < sz) {
				buffered = data[sz-1] & 0xFF;
				sz--;
			}
			else
				buffered = -1;
			sz = send_client_data(1, data, sz);
			if (sz < 0)
				goto fail;
		}

		/*
		 * We hit the keepalive timeout without saying anything; send
		 * an empty message on the data sideband just to let the other
		 * side know we're still working on it, but don't have any data
		 * yet.
		 *
		 * If we don't have a sideband channel, there's no room in the
		 * protocol to say anything, so those clients are just out of
		 * luck.
		 */
		if (!ret && use_sideband) {
			static const char buf[] = "0005\1";
			write_or_die(1, buf, 5);
		}
	}

	if (finish_command(&pack_objects)) {
		error("git upload-pack: git-pack-objects died with error.");
		goto fail;
	}

	/* flush the data */
	if (0 <= buffered) {
		data[0] = buffered;
		sz = send_client_data(1, data, 1);
		if (sz < 0)
			goto fail;
		fprintf(stderr, "flushed.\n");
	}
	if (use_sideband)
		packet_flush(1);
	return;

 fail:
	send_client_data(3, abort_msg, sizeof(abort_msg));
	die("git upload-pack: %s", abort_msg);
}