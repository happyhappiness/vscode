			if (do_compression && refused_compress) {
				create_refuse_error(refused_compress);
				return 0;
			}
			break;

		case OPT_WRITE_BATCH:
			/* batch_name is already set */
			write_batch = 1;
			break;

		case OPT_ONLY_WRITE_BATCH:
