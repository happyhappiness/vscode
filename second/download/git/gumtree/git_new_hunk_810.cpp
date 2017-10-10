			for (ref = remote_refs; ref; ref = ref->next)
				ref->status = REF_STATUS_NONE;
			if (args->stateless_rpc)
				close(out);
			if (git_connection_is_socket(conn))
				shutdown(fd[0], SHUT_WR);

			/*
			 * Do not even bother with the return value; we know we
			 * are failing, and just want the error() side effects.
			 */
			if (status_report)
				receive_unpack_status(in);

			if (use_sideband) {
				close(demux.out);
				finish_async(&demux);
			}
			fd[1] = -1;
			return -1;
