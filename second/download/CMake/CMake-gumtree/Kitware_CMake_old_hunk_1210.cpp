        sprintf(rpstr, "_p%d_", cc++);
        }
      while ( !done );
      m_UniqueObjectNamesMap[sin] = ssin;
      }
    }
  else
    {
    m_UniqueObjectNamesMap[sin] = sin;
    }
  return m_UniqueObjectNamesMap[sin];
}

//----------------------------------------------------------------------------
