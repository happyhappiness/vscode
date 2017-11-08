int bidirectional_transfer_loop(int input, int output)
{
	struct bidirectional_transfer_state state;

	/* Fill the state fields. */
	state.ptg.src = input;
	state.ptg.dest = 1;
	state.ptg.src_is_sock = (input == output);
	state.ptg.dest_is_sock = 0;
	state.ptg.state = SSTATE_TRANSFERRING;
	state.ptg.bufuse = 0;
	state.ptg.src_name = "remote input";
	state.ptg.dest_name = "stdout";

	state.gtp.src = 0;
	state.gtp.dest = output;
	state.gtp.src_is_sock = 0;
	state.gtp.dest_is_sock = (input == output);
	state.gtp.state = SSTATE_TRANSFERRING;
	state.gtp.bufuse = 0;
	state.gtp.src_name = "stdin";
	state.gtp.dest_name = "remote output";

	return tloop_spawnwait_tasks(&state);
}