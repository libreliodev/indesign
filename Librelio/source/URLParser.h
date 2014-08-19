#include <map>
#include <string>
#include <vector>

class URLParser
{
public:
	URLParser(void);
	~URLParser(void);
	
	void add(const std::string& key, const std::string& value);
    std::vector<std::string> getArgs();
    std::string getArgValue(const std::string &key, const std::string& defaultValue = "");
	std::string getURL();
	void parse(const std::string& value);
	void remove(const std::string& key);

private:
    std::map<std::string, std::string> m_argMap;
	std::vector<std::string> m_args;
	std::vector<std::string> m_parts;

	std::string join(std::vector<std::string> &vector, const std::string& delim);
	std::vector<std::string> split(const std::string &s, char delim);
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
};