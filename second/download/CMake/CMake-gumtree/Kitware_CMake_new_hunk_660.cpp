    CommandLineArguments::Internal::SetOfStrings::iterator sit;

    for ( sit = mpit->second.begin(); sit != mpit->second.end(); sit++ )

      {

      str << std::endl;

      char argument[100];

      sprintf(argument, "%s", sit->c_str());

      switch ( this->Internals->Callbacks[*sit].ArgumentType )

