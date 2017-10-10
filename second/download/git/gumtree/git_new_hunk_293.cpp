						 * on the next RPC request so the peer knows
						 * it is in common with us.
						 */
						const char *hex = sha1_to_hex(result_sha1);
						packet_buf_write(&req_buf, "have %s\n", hex);
						state_len = req_buf.len;
						/*
						 * Reset in_vain because an ack
						 * for this commit has not been
						 * seen.
						 */
						in_vain = 0;
					} else if (!args->stateless_rpc
						   || ack != ACK_common)
						in_vain = 0;
					mark_common(commit, 0, 1);
					retval = 0;
					got_continue = 1;
					if (ack == ACK_ready) {
						clear_prio_queue(&rev_list);
						got_ready = 1;
					}
					break;
