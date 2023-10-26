/**
 * Author:    Andrea Casalino
 * Created:   06.01.2020
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#ifndef HULL_ERROR_H
#define HULL_ERROR_H

#include <stdexcept>

namespace hull {
    class Error : public std::runtime_error {
    public:
      explicit Error(const std::string &what) : std::runtime_error(what){};
    };
} // namespace hull

#endif //HULL_ERROR_H