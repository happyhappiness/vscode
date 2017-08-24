{
#if defined(_WIN32) && !defined(__CYGWIN__)
			/* Avoid infinity wait.
			 * Note: If there is no data in the pipe, ReadFile()
			 * called in read() never returns and so we won't
			 * write remaining encoded data to the pipe.
			 * Note: This way may cause performance problem.
			 * we are looking forward to great code to resolve
			 * this.  */
			DWORD pipe_avail = -1;
			int cnt = 2;

			while (PeekNamedPipe(handle, NULL, 0, NULL,
			    &pipe_avail, NULL) != 0 && pipe_avail == 0 &&
			    cnt--)
				Sleep(5);
			if (pipe_avail == 0) {
				ret = -1;
				errno = EAGAIN;
				break;
			}
#endif
			ret = read(state->child_stdout, buf, requested);
		}