// Copyright (c) 2015-2018 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_FILE_INPUT_HPP
#define TAO_PEGTL_FILE_INPUT_HPP

#include "config.hpp"
#include "eol.hpp"
#include "tracking_mode.hpp"

#if defined( __unix__ ) || ( defined( __APPLE__ ) && defined( __MACH__ ) )
#include <unistd.h>  // Required for _POSIX_MAPPED_FILES
#endif

#if defined( _POSIX_MAPPED_FILES ) || defined( _WIN32 )
#include "mmap_input.hpp"
#else
#include "read_input.hpp"
#endif

namespace tao
{
   namespace TAO_PEGTL_NAMESPACE
   {
#if defined( _POSIX_MAPPED_FILES ) || defined( _WIN32 )

      template< tracking_mode P = tracking_mode::IMMEDIATE, typename Eol = eol::lf_crlf >
      struct file_input
         : mmap_input< P, Eol >
      {
         using mmap_input< P, Eol >::mmap_input;
      };

#ifdef __cpp_deduction_guides
      template< typename T >
      file_input( T&& in_filename )->file_input<>;
#endif

#else

      template< tracking_mode P = tracking_mode::IMMEDIATE, typename Eol = eol::lf_crlf >
      struct file_input
         : read_input< P, Eol >
      {
         using read_input< P, Eol >::read_input;
      };

#ifdef __cpp_deduction_guides
      template< typename T >
      file_input( T&& in_filename )->file_input<>;

      template< typename T >
      file_input( FILE* in_file, T&& in_filename )->file_input<>;
#endif

#endif

   }  // namespace TAO_PEGTL_NAMESPACE

}  // namespace tao

#endif
