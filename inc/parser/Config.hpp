#ifndef CONFIG_HPP
# define CONFIG_HPP
# include <map>
# include <unordered_map>
# include <unordered_set>
# include <iostream>

# include "colors.hpp"
# include "Parameters.hpp"
# include "Location.hpp"
# include "Listen.hpp"
# include "Exceptions.hpp"

# define DEF_CONF std::string("default/defaultConfig.conf")
# define DEF_NAME std::string("localhost")

class Config
{
	public:
		// Form
		Config(void) {};
		Config(const Config& copy);
		Config&	operator=(const Config& assign);
		virtual ~Config(void);

		void							parseBlock(std::vector<std::string>& block);
		const std::vector<Listen>& 		getListens(void) const;
		std::vector<Listen>& 			getListensNonConst(void);
		const std::vector<std::string>&	getNames(void) const;
		const std::string&				getPrimaryName(void) const;
		const Parameters&				getParams(void) const;
		const std::vector<Location>&	getLocations(void) const;

	private:
		std::vector<Listen> 		listens; // Listens
		std::vector<std::string>	names; // is the given "server_name".
		Parameters					params; // Default parameters for whole server block
		std::vector<Location>		locations; // declared Locations

		void	_parseListen(std::vector<std::string>& block);
		void	_parseServerName(std::vector<std::string>& block);
		void	_parseLocation(std::vector<std::string>& block);
		void	_fillServer(std::vector<std::string>& block);
};

#endif
