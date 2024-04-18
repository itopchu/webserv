#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <filesystem>
#include <chrono>			// timeout handling

#include "Exceptions.hpp"

#define HTTP_DEF_PORT		std::string("8080")			// default port, 80 if is
#define HTTP_DEF_SCHEME		std::string("HTTP")			// http scheme
#define HTTP_DEF_TERM		std::string("\r\n\r\n")		// http terminator
#define HTTP_DEF_NL			std::string("\r\n")			// http delimiter
#define HTTP_DEF_SP			' '							// shortcut for space
#define HTTP_DEF_VERSION	HTTP_DEF_SCHEME + std::string("/1.1")
#define HTTP_BUF_SIZE 		8192						// 8K
#define HTTP_MAX_TIMEOUT	10

// request headers
#define	HEADER_CONT_LEN			"Content-Length"
#define	HEADER_CONT_TYPE		"Content-Type"
#define	HEADER_HOST				"Host"
#define	HEADER_CONN				"Connection"
#define	HEADER_TRANS_ENCODING	"Transfer-Encoding"
#define	HEADER_COOKIE			"Cookie"
// response headers
#define HEADER_STATUS			"Status"
#define HEADER_DATE				"Date"
#define HEADER_SERVER			"Server"
#define HEADER_LOC				"Location"

using namespace std::chrono;

typedef std::multimap<std::string, std::string> t_dict;
typedef std::filesystem::path t_path;

typedef enum HTTPmethod_s
{
	HTTP_GET,
	HTTP_POST,
	HTTP_DELETE,
}	HTTPmethod;

typedef enum HTTPtype_s
{
	HTTP_STATIC,
	HTTP_REDIRECTION,
	HTTP_AUTOINDEX,
	HTTP_CGI_STATIC,
	HTTP_CGI_FILE_UPL,
	HTTP_DELETE_204,
}	HTTPtype;

typedef struct HTTPversion_f
{
	std::string	scheme;
	int			major;
	int			minor;
} HTTPversion;

class HTTPstruct
{
	public:
		HTTPstruct( int socket, int statusCode, HTTPtype type ) :
			_socket(socket),
			_statusCode(statusCode),
			_type(type),
			_version({HTTP_DEF_SCHEME, 1, 1}) {_resetTimeout();}
		virtual	~HTTPstruct( void ) {};

		virtual std::string	toString( void ) const noexcept =0;

		HTTPtype			getType( void ) const noexcept;
		int					getSocket( void ) const noexcept;
		int					getStatusCode( void ) const noexcept;
		std::string const&	getTmpBody( void ) const noexcept;
		void				setTmpBody( std::string const& ) noexcept;
		t_path const&		getRoot( void ) const noexcept;
		void				setRoot( t_path const& ) noexcept;

		bool	isStatic( void ) const noexcept;
		bool	isRedirection( void ) const noexcept;
		bool	isAutoIndex( void ) const noexcept;
		bool	isFastCGI( void ) const noexcept;
		bool	isFileUpload( void ) const noexcept;
		bool	isDelete( void ) const noexcept;
		bool	isCGI( void ) const noexcept;

	protected:
		int			_socket, _statusCode;
		HTTPtype	_type;

		t_dict 		_headers;
		std::string	_tmpBody, _body;
    	HTTPversion	_version;
		t_path		_root;

		steady_clock::time_point	_lastActivity;

		virtual void	_setHead( std::string const& ) {};
		virtual void	_setHeaders( std::string const& );
		virtual void	_setVersion( std::string const& );
		virtual void	_setBody( std::string const& tmpBody );

		void	_resetTimeout( void ) noexcept;
		void	_checkTimeout( void );

		void	_addHeader(std::string const&, std::string const& ) noexcept;
	};
