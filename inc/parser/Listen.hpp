#ifndef LISTEN_HPP
# define LISTEN_HPP
# include <string>
# include <vector>
# include <cstdint>

# include "Exceptions.hpp"

# define DEF_PORT "8080"
# define DEF_HOST "127.0.0.1"
# define MAX_PORT 65535

class Listen
{
	public:
		Listen(const Listen& copy);
		Listen&	operator=(const Listen& assign);
		Listen(void);
		virtual ~Listen(void);

		void						fillValues(std::vector<std::string>& block);
		void						setDef(bool);
		const std::string&			getIpString(void) const;
		const std::vector<uint8_t>&	getIpInt(void) const;
		const std::string&			getPortString(void) const;
		const uint16_t&				getPortInt(void) const;
		const bool&					getDef(void) const;
		bool						operator==(const Listen&) const;
		bool						operator!=(const Listen&) const;

	private:
		uint16_t				i_port;	// Port val;
		std::vector<uint8_t>	i_ip;	// Ip vals
		std::string				s_ip;	// String ip
		std::string				s_port;	// String port
		bool					def;	// Check for default_server

		void	_fillFull(std::vector<std::string>& block);
		void	_fillIp(std::vector<std::string>& block);
		void	_fillPort(std::vector<std::string>& block);
};

#endif