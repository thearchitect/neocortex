#pragma once
#include <string>

class Exception
{
public:
	Exception(const std::string& in_rMessage) : 
	  m_message(in_rMessage) {}

	  const std::string& GetErrorMessage() const { return m_message; }

private:
	std::string m_message;
};