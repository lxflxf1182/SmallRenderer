#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <iostream>

std::string& str_replace(const std::string& search, const std::string& replace, std::string& subject);

void Throw(const std::string& msg_);

#endif // !UTIL_H
