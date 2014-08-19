#include "URLParser.h"

#include <algorithm>
#include <sstream>

URLParser::URLParser(void)
{
}

URLParser::~URLParser(void)
{
}

void URLParser::add(const std::string& key, const std::string& value)
{
	this->remove(key);
	m_args.push_back(key + "=" + value);
}

std::vector<std::string> URLParser::getArgs()
{
    return m_args;
}

std::string URLParser::getArgValue(const std::string& key, const std::string& defaultValue)
{
    std::string value = defaultValue;
    
    if(m_argMap.find(key) != m_argMap.end())
    {
        value = m_argMap[key];
    }
    
    return value;
}

std::string URLParser::getURL()
{
	std::string args = this->join(m_args, "&");
	std::string url = m_parts[0];

	if(args.length() > 0)
	{
		url.append("?");
	}

	url.append(args);

	return url;
}

void URLParser::parse(const std::string& url)
{
    std::vector<std::string>::iterator it;
    std::vector<std::string> keyValue;
    std::string key;
    std::string value;
    
	m_parts = this->split(url, '?');

	if(m_parts.size() > 1)
	{
		m_args = this->split(m_parts[1], '&');
	}
    
	for(it = m_args.begin(); it != m_args.end(); ++it)
	{
        keyValue = this->split(*it, '=');
        
        if(keyValue.size() == 2)
        {
            key = keyValue[0];
            value = keyValue[1];
            
            m_argMap[key] = value;
        }
    }
}

void URLParser::remove(const std::string& key)
{
	std::string value = "";
	std::vector<std::string>::iterator it;

	for(it = m_args.begin(); it != m_args.end(); ++it)
	{
		if(it->find(key) != std::string::npos)
		{
			value = *it;
		}
	}

	if(value.length() > 0)
	{
		it = std::remove(m_args.begin(), m_args.end(), value);
		m_args.erase(it);
	}
}

//
// Private
//

std::string URLParser::join(std::vector<std::string> &vector, const std::string& delim)
{
	std::string result;

	for(int index = 0; index < vector.size(); index++)
	{
		result.append(vector[index]);

		if(index < vector.size() - 1)
		{
			result.append(delim);
		}
	}

	return result;
}

std::vector<std::string> &URLParser::split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
    std::stringstream ss(s);
    std::string item;

	while (std::getline(ss, item, delim)) 
	{
        elems.push_back(item);
    }

    return elems;
}

std::vector<std::string> URLParser::split(const std::string &s, char delim) 
{
    std::vector<std::string> elems;
    
	split(s, delim, elems);

    return elems;
}