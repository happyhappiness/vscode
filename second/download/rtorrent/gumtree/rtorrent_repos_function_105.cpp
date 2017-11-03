int
main(int argc, char** argv) {
  try {

    // Temporary.
    setlocale(LC_ALL, "");

    cachedTime = rak::timer::current();

    control = new Control;
    
    srandom(cachedTime.usec());
    srand48(cachedTime.usec());

    SignalHandler::set_ignore(SIGPIPE);
    SignalHandler::set_handler(SIGINT,   sigc::mem_fun(control, &Control::receive_normal_shutdown));
    SignalHandler::set_handler(SIGTERM,  sigc::mem_fun(control, &Control::receive_quick_shutdown));
    SignalHandler::set_handler(SIGWINCH, sigc::mem_fun(control->display(), &display::Manager::force_redraw));
    SignalHandler::set_handler(SIGSEGV,  sigc::bind(sigc::ptr_fun(&do_panic), SIGSEGV));
    SignalHandler::set_handler(SIGBUS,   sigc::bind(sigc::ptr_fun(&do_panic), SIGBUS));
    SignalHandler::set_handler(SIGFPE,   sigc::bind(sigc::ptr_fun(&do_panic), SIGFPE));

    control->core()->initialize_first();

    // Initialize option handlers after libtorrent to ensure
    // torrent::ConnectionManager* are valid etc.
    initialize_commands();

    rpc::parse_command_multiple(
       // Currently not doing any sorting on main.
       "view_add = main\n"
       "view_add = default\n"

       "view_add = name\n"
       "view_sort_new = name,name\n"
       "view_sort_current = name,name\n"

       "view_add = started\n"
       "view_filter = started,started\n"
       "view_filter_on = started,start,stop\n"
       "view_sort_new = started,name\n"
       "view_sort_current = started,name\n"

       "view_add = stopped\n"
       "view_filter = stopped,stopped\n"
       "view_filter_on = stopped,start,stop\n"
       "view_sort_new = stopped,name\n"
       "view_sort_current = stopped,name\n"

       "view_add = complete\n"
       "view_filter = complete,complete\n"
       "view_filter_on = complete,hash_done,finished\n"
       "view_sort_new = complete,state_changed\n"
       "view_sort_current = complete,state_changed_reverse\n"

       "view_add = incomplete\n"
       "view_filter = incomplete,incomplete\n"
       "view_filter_on = incomplete,hash_done,finished\n"
       "view_sort_new = incomplete,state_changed\n"
       "view_sort_current = incomplete,state_changed_reverse\n"

       // The hashing view does not include stopped torrents.
       "view_add = hashing\n"
       "view_filter = hashing,hashing\n"
       "view_filter_on = hashing,hash_queued,hash_removed,hash_done\n"
       "view_sort_new = hashing,state_changed\n"
       "view_sort_current = hashing,state_changed\n"

       "view_add = seeding\n"
       "view_filter = seeding,started,complete\n"
       "view_filter_on = seeding,start,stop\n"
       "view_sort_new = seeding,state_changed\n"
       "view_sort_current = seeding,state_changed_reverse\n"

       "schedule = view_main,10,10,\"view_sort=main,20\"\n"
       "schedule = view_name,10,10,\"view_sort=name,20\"\n"
       //     "schedule = view_started,10,10,view_sort=started,5\n"
       //     "schedule = view_stopped,10,10,view_sort=stopped,5\n"
       //     "schedule = view_complete,10,10,view_sort=complete,5\n"
       //     "schedule = view_incomplete,10,10,view_sort=incomplete,5\n"

       //"schedule = scheduler,10,10,download_scheduler=\n"
       "schedule = session_save,1800,1800,session_save=\n"
       "schedule = low_diskspace,5,60,close_low_diskspace=500M\n"

       // Changing these will bork the (non-existant) scheduler.
       "view_add = scheduler\n"
       "view_sort_new = scheduler,state_changed\n" // add started?
       "view_sort_current = scheduler,state_changed\n"

       //    "schedule = scheduler,10,10,download_scheduler=\n"
    );

    if (OptionParser::has_flag('n', argc, argv))
      control->core()->push_log("Ignoring ~/.rtorrent.rc.");
    else
      rpc::parse_command_single("try_import = ~/.rtorrent.rc");

    int firstArg = parse_options(control, argc, argv);

    control->initialize();

    // Load session torrents and perform scheduled tasks to ensure
    // session torrents are loaded before arg torrents.
    load_session_torrents(control);
    rak::priority_queue_perform(&taskScheduler, cachedTime);

    load_arg_torrents(control, argv + firstArg, argv + argc);

    // Make sure we update the display before any scheduled tasks can
    // run, so that loading of torrents doesn't look like it hangs on
    // startup.
    control->display()->adjust_layout();
    control->display()->receive_update();

    while (!control->is_shutdown_completed()) {
      if (control->is_shutdown_received())
        control->handle_shutdown();

      control->inc_tick();

      cachedTime = rak::timer::current();
      rak::priority_queue_perform(&taskScheduler, cachedTime);

      // Do shutdown check before poll, not after.
      control->core()->get_poll_manager()->poll(client_next_timeout(control));
    }

    control->core()->download_list()->session_save();

    control->cleanup();

  } catch (std::exception& e) {
    display::Canvas::cleanup();

    // Safe to delete here? Seem to cause problems if cleanup hasn't
    // been called.
    //delete control;

    std::cout << "rtorrent: " << e.what() << std::endl;
    return -1;
  }

  delete control;

  return 0;
}