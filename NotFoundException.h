
/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for an object thrown on violation of precondition.
 *
 *  Adapted from page 250 in Carrano 7e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Rudolf Musika
 *
 *  @date 7 Feb 2018
 *
 *  @version 7.0 */

#ifndef NOT_FOUND_EXCEP_
#define NOT_FOUND_EXCEP_

#include <stdexcept>
#include <string>

/** @class NotFoundExcept NotFoundExcept.h "NotFoundExcept.h"
 *
 *  Specification for an object thrown on violation of precondition. */
class NotFoundException : public std::logic_error {
    //class NotFoundException : public std::runtime_error {
public:
    explicit NotFoundException(const std::string& message = "");

    virtual ~NotFoundException() noexcept = default; //throw();
};


#endif
