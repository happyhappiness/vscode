			if (do_compression && refused_compress) {
				create_refuse_error(refused_compress);
				return 0;
			}
			break;

		case 'M':
			arg = poptGetOptArg(pc);
			if (*arg != '-') {
				snprintf(err_buf, sizeof err_buf,
					"Remote option must start with a dash: %s\n", arg);
				return 0;
			}
			if (remote_option_cnt+2 >= remote_option_alloc) {
				remote_option_alloc += 16;
				remote_options = realloc_array(remote_options,
							const char *, remote_option_alloc);
				if (!remote_options)
					out_of_memory("parse_arguments");
				if (!remote_option_cnt)
					remote_options[0] = "ARG0";
			}
			remote_options[++remote_option_cnt] = arg;
			remote_options[remote_option_cnt+1] = NULL;
			break;

		case OPT_WRITE_BATCH:
			/* batch_name is already set */
			write_batch = 1;
			break;

		case OPT_ONLY_WRITE_BATCH:
