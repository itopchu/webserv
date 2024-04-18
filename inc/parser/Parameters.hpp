#ifndef PARAMETERS_HPP
# define PARAMETERS_HPP
# include <vector>
# include <string>
# include <unordered_set>
# include <map>
# include <climits>
# include <cstdint>
# include <stdexcept>
# include <iostream>
# include <bitset>
# include <filesystem>

# include "Exceptions.hpp"
# include "HTTPstruct.hpp"

# define METHOD_AMOUNT 3u // amount of methodes used in our program
# define DEF_SIZE 10
# define DEF_ROOT t_path("/var/www")
# define MAX_SIZE 20
# define DEF_CGI_ALLOWED false
# define DEF_CGI_EXTENTION ".cgi"
# define DEF_SIZE_VALUE 'B'

typedef	std::filesystem::path	t_path;
typedef std::map<size_t, t_path> t_path_map;

class Parameters
{
	public:
		Parameters(void);
		virtual ~Parameters(void);
		Parameters(const Parameters& copy);
		Parameters&	operator=(const Parameters& assign);

		void	fill(std::vector<std::string>& block);
		void	setRoot(t_path val);
		void	setSize(uintmax_t val, char *c);
		void	setAutoindex(bool status);

		void								inherit(Parameters const&);
		const std::pair<size_t, t_path>& 	getReturns(void) const;
		const std::vector<t_path>&	 		getIndex(void) const;
		std::uintmax_t						getMaxSize(void) const;
		const t_path_map& 					getErrorPages(void) const;
		const bool& 						getAutoindex(void) const;
		const t_path& 						getRoot(void) const;
		const std::bitset<METHOD_AMOUNT>&	getAllowedMethods(void) const;
		const std::string& 					getCgiExtension(void) const;
		const bool& 						getCgiAllowed(void) const;

	private:
		std::uintmax_t				max_size;	// Will be overwriten by last found
		bool						autoindex;	// FALSE in default, will be overwriten.
		std::vector<t_path>			index;	// Will be searched in given order
		t_path						root;		// Last found will be used.
		t_path_map					error_pages;	// Same status codes will be overwriten
		std::pair<size_t, t_path>	returns;	// Overwritten by the last
		std::bitset<METHOD_AMOUNT>	allowedMethods;	// Allowed methods
		std::string					cgi_extension;	// extention .py .sh
		bool						cgi_allowed;	// Check for permissions

		void	_parseRoot(std::vector<std::string>& block);
		void	_parseBodySize(std::vector<std::string>& block);
		void	_parseAutoindex(std::vector<std::string>& block);
		void	_parseIndex(std::vector<std::string>& block);
		void	_parseErrorPage(std::vector<std::string>& block);
		void	_parseReturn(std::vector<std::string>& block);
		void	_parseAllowMethod(std::vector<std::string>& block);
		void	_parseDenyMethod(std::vector<std::string>& block);
		void	_parseCgiExtension(std::vector<std::string>& block);
		void	_parseCgiAllowed(std::vector<std::string>& block);
};

#endif