#ifndef REQUESTVALIDATE_HPP
# define REQUESTVALIDATE_HPP
# include "HTTPstruct.hpp"
# include "Config.hpp"
# include <iostream>
# include <fstream>
# include "Exceptions.hpp"

typedef std::filesystem::perms t_perms;

typedef enum PermType_s
{
	PERM_READ,
	PERM_WRITE,
	PERM_EXEC,
} PermType;

typedef std::vector<Config> t_serv_list;

class RequestValidate
{
	public:
		RequestValidate( t_serv_list const& );
		virtual	~RequestValidate( void );

		void	solvePath( HTTPmethod, t_path const&, std::string const& );
		void	solveErrorPath( int );

		t_path const&		getRealPath( void ) const;
		t_path const&		getRedirectRealPath( void ) const;
		std::string const&	getServName( void ) const;
		std::uintmax_t		getMaxBodySize( void ) const;
		int					getStatusCode( void ) const;
		t_path const&		getRoot( void ) const;
		bool				isAutoIndex( void ) const;
		bool				isFile( void ) const;
		bool				isCGI( void ) const;
		bool				isRedirection( void ) const;
		bool				solvePathFailed( void ) const;

	private:
		t_serv_list		_servers;
		Config			*_defaultServer, *_handlerServer;
		HTTPmethod		_requestMethod;
		t_path			_requestPath;

		size_t	_statusCode;
		t_path	_realPath, _redirectRealPath;
		bool	_autoIndex;
		bool	_isCGI;
		bool	_isRedirection;

		Location const*		_validLocation;
		Parameters const*	_validParams;

		t_path				targetDir;
		t_path				targetFile;

		void			_resetValues( void );
		void			_setConfig( std::string const& );
		void			_setMethod( HTTPmethod );
		void			_setPath( t_path const& );
		bool			_hasValidIndex( void ) const;

		bool			_checkPerm(t_path const& path, PermType type);
		void			_separateFolders(std::string const& input, std::vector<std::string>& output);
		Location const*	_diveLocation(Location const& cur, std::vector<std::string>::iterator itDirectory, std::vector<std::string>& folders);

		void	_initValidLocation( void );
		void	_initTargetElements( void );

		bool	_handleFolder( void );
		bool	_handleFile( void );
		bool	_handleReturns( void );
		void	_handleIndex( void );

		void		_setStatusCode(const size_t& code);
};

#endif
