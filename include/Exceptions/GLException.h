#ifndef GL_EXCEPTION
#define GL_EXCEPTION

#include <string>
#include <iostream>
#include <exception>

class GLException : public std::exception
{
protected:
  std::string message;

public:
  explicit GLException(const std::string &s);
  virtual std::string GetMessage() const;
};

std::ostream &operator<<(std::ostream &os, const GLException &e);
GLException::GLException(const std::string &s) : message(s)
{
}

std::string GLException::GetMessage() const
{
  return message;
}

std::ostream &operator<<(std::ostream &os, const GLException &e)
{
  return os << e.GetMessage();
}
#endif
