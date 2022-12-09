#ifndef NEGATIVE_CYCLE_EXCEPTION
#define NEGATIVE_CYCLE_EXCEPTION

#include <Exceptions/GLException.h>

class NegativeCycleException : public GLException
{
public:
    NegativeCycleException(const std::string &s);
    ~NegativeCycleException();
};
NegativeCycleException::NegativeCycleException(const std::string &s) : GLException(s)
{
}

NegativeCycleException::~NegativeCycleException()
{
}
#endif