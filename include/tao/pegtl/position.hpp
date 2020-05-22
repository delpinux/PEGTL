// Copyright (c) 2014-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_POSITION_HPP
#define TAO_PEGTL_POSITION_HPP

#include <cstdlib>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

#include "config.hpp"

#include "internal/iterator.hpp"

namespace TAO_PEGTL_NAMESPACE
{
   struct position
   {
      position() = delete;

      position( position&& p ) noexcept
         : byte( p.byte ),
           line( p.line ),
           column( p.column ),
           source( std::move( p.source ) )
      {}

      position( const position& ) = default;

      position& operator=( position&& p ) noexcept
      {
         byte = p.byte;
         line = p.line;
         column = p.column;
         source = std::move( p.source );
         return *this;
      }

      position& operator=( const position& ) = default;

      template< typename T >
      position( const internal::iterator& in_iter, T&& in_source )
         : byte( in_iter.byte ),
           line( in_iter.line ),
           column( in_iter.column ),
           source( std::forward< T >( in_source ) )
      {}

      ~position() = default;

      std::size_t byte;
      std::size_t line;
      std::size_t column;
      std::string source;
   };

   inline bool operator==( const position& lhs, const position& rhs ) noexcept
   {
      return ( lhs.byte == rhs.byte ) && ( lhs.source == rhs.source );
   }

   inline bool operator!=( const position& lhs, const position& rhs ) noexcept
   {
      return !( lhs == rhs );
   }

   inline std::ostream& operator<<( std::ostream& os, const position& p )
   {
      return os << p.source << ':' << p.line << ':' << p.column;
   }

   [[nodiscard]] inline std::string to_string( const position& p )
   {
      std::ostringstream o;
      o << p;
      return o.str();
   }

}  // namespace TAO_PEGTL_NAMESPACE

#endif
