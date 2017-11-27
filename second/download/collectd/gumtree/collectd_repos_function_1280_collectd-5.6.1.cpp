grpc::Status queryValuesRead(value_list_t const *match, std::queue<value_list_t> *value_lists) {
		uc_iter_t *iter;
		if ((iter = uc_get_iterator()) == NULL) {
			return grpc::Status(grpc::StatusCode::INTERNAL,
								grpc::string("failed to query values: cannot create iterator"));
		}

		grpc::Status status = grpc::Status::OK;
		char *name = NULL;
		while (uc_iterator_next(iter, &name) == 0) {
			value_list_t vl;
			if (parse_identifier_vl(name, &vl) != 0) {
				status = grpc::Status(grpc::StatusCode::INTERNAL,
									  grpc::string("failed to parse identifier"));
				break;
			}

			if (!ident_matches(&vl, match))
				continue;

			if (uc_iterator_get_time(iter, &vl.time) < 0) {
				status = grpc::Status(grpc::StatusCode::INTERNAL,
									  grpc::string("failed to retrieve value timestamp"));
				break;
			}
			if (uc_iterator_get_interval(iter, &vl.interval) < 0) {
				status = grpc::Status(grpc::StatusCode::INTERNAL,
									  grpc::string("failed to retrieve value interval"));
				break;
			}
			if (uc_iterator_get_values(iter, &vl.values, &vl.values_len) < 0) {
				status = grpc::Status(grpc::StatusCode::INTERNAL,
									  grpc::string("failed to retrieve values"));
				break;
			}

			value_lists->push(vl);
		} // while (uc_iterator_next(iter, &name) == 0)

		uc_iterator_destroy(iter);
		return status;
	}