#include "Links/CompoMe/Zmq/Zmq_client_out/Zmq_client_out.hpp"

namespace CompoMe {

namespace Zmq {

//============================= addr =============================
CompoMe::String Zmq_client_out::get_addr() const { return this->addr; }

void Zmq_client_out::set_addr(const CompoMe::String p_addr) {
  this->addr = p_addr;
}

CompoMe::String &Zmq_client_out::a_addr() { return this->addr; }
//--------------------------------------------------------------------------

// Get Port /////////////////////////////////////////////////////////////

CompoMe::Stream::out &Zmq_client_out::get_main() { return this->main; }
CompoMe::Stream::map_out &Zmq_client_out::get_many() { return this->many; }

} // namespace Zmq

} // namespace CompoMe
